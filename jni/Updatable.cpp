#include "Updatable.h"
#include "Render.h"
#include "Materials/Material.h"

bool Updatable::focusIsCheck = false;
bool Updatable::keyUpIsCheck = false;
bool Updatable::keyDownIsCheck = false;
Updatable* Updatable::objectFocused = NULL;

Updatable::Updatable(Updatable *parent) : m_parent(NULL), m_updateFocus(true), m_canUpdate(true), m_canDraw(true), m_applyMatrix(NULL)
{
	if(parent)
		parent->addChild(this);
}

Updatable::~Updatable()
{
	if(Updatable::objectFocused == this)
		Updatable::objectFocused = NULL;

	setParent(NULL);
}

void Updatable::updateFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(!m_updateFocus || !m_canUpdate || Updatable::focusIsCheck)
		return;


	//Handle clipping. Might change the onUpdate outcome
	bool restoreClip = false;
	bool mEnableClip = Material::getGlobalEnableClipping();
	Rectangle2f clip;

	if(m_enableClipping)
	{
		if(Material::getGlobalEnableClipping())
		{
			restoreClip = true;
			clip = Material::getGlobalClipping();

			Rectangle2f r = getRectIntersect(clip, m_clip);

			Material::setGlobalClipping(r);
		}

		else
		{
			Material::enableGlobalClipping(true);
			Material::setGlobalClipping(m_clip);
		}
	}

	for(std::list<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); ++it)
	{
		(*it)->updateFocus(te, render, mvp);
		if(Updatable::focusIsCheck == true)
			return;
	}

	if(testFocus(te, render, mvp))
	{
		onFocus(te, render, mvp);
		Updatable::objectFocused = this;
		Updatable::focusIsCheck = true;
		return;
	}

	if(restoreClip)
	{
		Material::enableGlobalClipping(mEnableClip);
		Material::setGlobalClipping(clip);
	}

	else if(!mEnableClip)
		Material::enableGlobalClipping(false);
}

bool Updatable::testFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	return false;
}

void Updatable::onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	Updatable::objectFocused = this;
	Updatable::focusIsCheck = true;
	LOG_DEBUG("Focus !");
	if(m_focusListener)
	{
		LOG_DEBUG("FIRE !");
		m_focusListener->fire();
	}
}

void Updatable::keyUp(int32_t keyCode)
{
	for(std::list<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); it++)
	{
		(*it)->keyUp(keyCode);
		if(Updatable::keyUpIsCheck == true)
			return;
	}
	if(onKeyUp(keyCode))
		Updatable::keyUpIsCheck = true;
}

void Updatable::keyDown(int32_t keyCode)
{
	for(std::list<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); it++)
	{
		(*it)->keyDown(keyCode);
		if(Updatable::keyDownIsCheck == true)
			return;
	}

	if(onKeyDown(keyCode))
		Updatable::keyDownIsCheck = true;
}

bool Updatable::onKeyUp(int32_t keyCode)
{
	return false;
}

bool Updatable::onKeyDown(int32_t keyCode)
{
	return false;
}

void Updatable::moveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	for(std::list<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); it++)
		(*it)->moveEvent(te, render, mvp);

	onMoveEvent(te, render, mvp);
}

void Updatable::onMoveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{}

void Updatable::update(Render &render)
{
	if(!m_canUpdate)
		return;
	onUpdate(render);
	for(std::list<Updatable*>::iterator it = m_child.begin(); it!=m_child.end(); ++it)
		if(*it)
			(*it)->update(render);
}

void Updatable::updateGPU(Render& render)
{
	if(!m_canDraw)
		return;

	bool restoreClip = false;
	bool mEnableClip = Material::getGlobalEnableClipping();
	Rectangle2f clip;

	if(m_enableClipping)
	{
		if(Material::getGlobalEnableClipping())
		{
			restoreClip = true;
			clip = Material::getGlobalClipping();

			Rectangle2f r = getRectIntersect(clip, m_clip);

			Material::setGlobalClipping(r);
		}

		else
		{
			Material::enableGlobalClipping(true);
			Material::setGlobalClipping(m_clip);
		}
	}

	for(std::list<Updatable*>::iterator it = m_child.begin(); it!=m_child.end(); ++it)
		if(*it)
			(*it)->updateGPU(render);

	if(restoreClip)
	{
		Material::enableGlobalClipping(mEnableClip);
		Material::setGlobalClipping(clip);
	}

	else if(!mEnableClip)
		Material::enableGlobalClipping(false);
}

void Updatable::onUpdate(Render &render)
{}

void Updatable::updateTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(Updatable::objectFocused == this)
	{
		onTouchUp(te, render, mvp);
		return;
	}

	for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); it++)
		(*it)->updateTouchUp(te, render, mvp);
}

void Updatable::onTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{}

void Updatable::addChild(Updatable *child, int pos)
{
	if(child->m_parent != this)
		child->setParent(this, pos);

	if(child != NULL && !isChild(child))
	{
		if(pos < 0 || (uint32_t)(pos) >= m_child.size())
			m_child.push_back(child);

		else
		{
			std::list<Updatable*>::iterator it = m_child.begin();
			for(int i=0; i < pos; i++)
				it++;
			m_child.insert(it, child);
		}
	}
}

void Updatable::setUpdateFocus(bool u)
{
	m_updateFocus = u;
}

void Updatable::setCanUpdate(bool u)
{
	m_canUpdate = u;
}

void Updatable::setCanDraw(bool d)
{
	m_canDraw = d;
}

void Updatable::setParent(Updatable *parent, int pos)
{

	if(m_parent)
	{
		delParentTransformable();
		m_parent->removeChild(this);
	}
	
	m_parent = parent;	

	if(m_parent)
	{
		addParentTransformable(parent);
		m_parent->addChild(this, pos);
	}
}

void Updatable::clearChild()
{
	for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
		(*it)->setParent(NULL);
}

bool Updatable::removeChild(Updatable *child)
{
	if(child->getParent() == this)
	{
		for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
		{
			if(*it == child)
			{
				m_child.erase(it);
				child->m_parent = NULL;
				return true;
			}
		}
	}
	return false;
}

bool Updatable::removeChild(unsigned int pos)
{
	if(pos >= m_child.size())
		return false;

	std::list<Updatable*>::iterator it = m_child.begin();
	for(unsigned int i = 0; i != pos; i++)
		it++;

	(*it)->setParent(NULL);
	return true;
}

bool Updatable::isChild(const Updatable *child)
{
	bool isChild = false;

	for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
		if((*it) == child)
		{
			isChild = true;
			break;
		}

	return isChild;
}

bool Updatable::getCanUpdate() const
{
	return m_canUpdate;
}

bool Updatable::canDraw() const
{
	return m_canDraw;
}

const Updatable* Updatable::getParent() const
{
	return m_parent;
}

Render* Updatable::getRenderParent()
{
	return (m_parent) ? m_parent->getRenderParent() : NULL;
}

void Updatable::setClipping(const Rectangle2f& clip)
{
	m_clip = clip;
}

void Updatable::enableClipping(bool enable)
{
	m_enableClipping = enable;
}

const Rectangle2f& Updatable::getClipping() const
{
	return m_clip;
}

bool Updatable::getEnableClipping() const
{
	return m_enableClipping;
}

void Updatable::setChildrenTransformable(const Transformable* tr)
{
	m_applyMatrix = tr;
}

void Updatable::addParentTransformable(const Updatable* parent)
{
	m_parentTransformables = parent->m_parentTransformables;
	m_parentTransformables.push_back(parent);

	for(auto* it : m_child)
		it->addParentTransformable(this);
}

void Updatable::delParentTransformable()
{
	m_parentTransformables.clear();
	for(auto* it : m_child)
		it->addParentTransformable(this);
}

Rectangle3f Updatable::getGlobalRect() const
{
	if(m_child.size() > 0)
	{
		Rectangle3f rect = (*(m_child.begin()))->getGlobalRect();
		std::list<Updatable*>::const_iterator it = m_child.begin();
		it++;
		for(;it != m_child.end(); ++it)
			rect = getRectAddiction(rect, (*it)->getGlobalRect());
		return rect;
	}
	return Rectangle3f();
}

glm::mat4 Updatable::getApplyChildrenMatrix() const
{
	if(m_parent)
	{
		return m_parent->getApplyChildrenMatrix() * ((m_applyMatrix) ? m_applyMatrix->Transformable::getMatrix() : glm::mat4(1.0f));
	}
	return (m_applyMatrix) ? m_applyMatrix->Transformable::getMatrix() : glm::mat4(1.0f);
}

const Transformable* Updatable::getApplyChildrenTransformable() const
{
	return m_applyMatrix;
}
