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
	m_iterDelete = m_child.end();
}

Updatable::~Updatable()
{
	if(Updatable::objectFocused == this)
		Updatable::objectFocused = NULL;

	setParent(NULL);
	clearChild();
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
			clip = Material::getGlobalClipping();
			Rectangle2f r = getRectIntersect(clip, m_clip);
			Material::setGlobalClipping(r);
			restoreClip = true;
		}

		else
		{
			Material::enableGlobalClipping(true);
			Material::setGlobalClipping(m_clip);
		}
	}

	for(std::vector<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); ++it)
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

	Material::enableGlobalClipping(mEnableClip);
	if(restoreClip)
		Material::setGlobalClipping(clip);
}

bool Updatable::testFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	return false;
}

void Updatable::onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	Updatable::objectFocused = this;
	Updatable::focusIsCheck = true;
	if(m_focusListener)
		m_focusListener->fire();
}

void Updatable::keyUp(int32_t keyCode)
{
	for(std::vector<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); it++)
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
	for(std::vector<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); it++)
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
	for(std::vector<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); it++)
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
	std::vector<Updatable*>::iterator it = m_child.begin();
	while(it!=m_child.end())
	{
		(*it)->update(render);
		if(m_hasErase)
		{
			it = m_iterDelete;
			m_hasErase = false;
		}
		else
			it++;
	}
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

	for(std::vector<Updatable*>::iterator it = m_child.begin(); it!=m_child.end(); ++it)
		(*it)->updateGPU(render);

	Material::enableGlobalClipping(mEnableClip);
	if(restoreClip)
		Material::setGlobalClipping(clip);
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

	std::vector<Updatable*>::iterator it = m_child.begin();
	while(it!=m_child.end())
	{
		if(*it)
			(*it)->updateTouchUp(te, render, mvp);
		if(m_hasErase)
		{
			it = m_iterDelete;
			m_hasErase = false;
		}
		else
			it++;
	}
}

void Updatable::onTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{}

void Updatable::addChild(Updatable *child, int pos)
{
	if(child->m_parent != this)
		child->setParent(this, pos);

	if(child != NULL && !isChild(child))
	{
		if(pos < 0 || pos >= (int)(m_child.size()))
			m_child.push_back(child);

		else
		{
			std::vector<Updatable*>::iterator it = m_child.begin();
			std::advance(it, pos);
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
		m_parent->removeChild(this);
	
	m_parent = parent;	

	if(parent)
		m_parent->addChild(this, pos);
}

void Updatable::clearChild()
{
	for(std::vector<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
		(*it)->m_parent = NULL;
	m_child.clear();
}

bool Updatable::removeChild(Updatable *child)
{
	if(child->getParent() == this)
	{
		for(std::vector<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
		{
			if(*it == child)
			{
				m_iterDelete = m_child.erase(it);
				child->m_parent = NULL;
				m_hasErase = true;
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

	std::vector<Updatable*>::iterator it = m_child.begin();
	std::advance(it, pos);

	(*it)->setParent(NULL);
	return true;
}

bool Updatable::isChild(const Updatable *child)
{
	bool isChild = false;

	for(std::vector<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
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

Rectangle3f Updatable::getGlobalRect() const
{
	if(m_child.size() > 0)
	{
		Rectangle3f rect = (*(m_child.begin()))->getGlobalRect();
		std::vector<Updatable*>::const_iterator it = m_child.begin();
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
		if(m_applyMatrix)
			return m_parent->getApplyChildrenMatrix() * m_applyMatrix->getMatrix();
		else
			return m_parent->getApplyChildrenMatrix();
	}

	return (m_applyMatrix) ? m_applyMatrix->Transformable::getMatrix() : glm::mat4(1.0f);
}

const Transformable* Updatable::getApplyChildrenTransformable() const
{
	return m_applyMatrix;
}
