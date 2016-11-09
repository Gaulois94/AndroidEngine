#include "Updatable.h"
#include "Render.h"
#include "Materials/Material.h"

bool Updatable::focusIsCheck = false;
bool Updatable::keyUpIsCheck = false;
bool Updatable::keyDownIsCheck = false;
Updatable* Updatable::objectFocused = NULL;

Updatable::Updatable(Updatable *parent) : m_parent(NULL), m_updateFocus(true), m_canUpdate(true), m_canDraw(true)
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
	if(!m_updateFocus || !m_canUpdate)
		return;

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
}

bool Updatable::testFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	return false;
}

void Updatable::onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	Updatable::objectFocused = this;
	Updatable::focusIsCheck = true;
	if(m_focusCallback)
		m_focusCallback(this, m_focusDatas);
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
	if(!m_canUpdate || !m_canDraw)
		return;

	bool restoreClip = false;
	bool mEnableClip = Material::getGlobalEnableClipping();
	Clipping clip;

	if(m_enableClipping)
	{
		if(Material::getGlobalEnableClipping())
		{
			restoreClip = true;
			clip = Material::getGlobalClipping();

			Rectangle2f r = getRectIntersect(Rectangle2f(clip.x, clip.y, clip.height, clip.width), Rectangle2f(m_clip.x, m_clip.y, m_clip.height, m_clip.width));

			clip.x = r.x;
			clip.y = r.y;
			clip.width = r.width;
			clip.height = r.height;

			Material::setGlobalClipping(clip);
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
}

void Updatable::onUpdate(Render &render)
{}

void Updatable::onTouchUp(const TouchEvent& te)
{}

void Updatable::addChild(Updatable *child, int pos)
{
	if(child->m_parent != this)
		child->setParent(this, pos);

	if(child != NULL && !isChild(child))
	{
		if(pos < 0 || pos >= m_child.size())
			m_child.push_back(child);

		else
		{
			std::list<Updatable*>::iterator it = m_child.begin();
			for(unsigned int i = 0; i < pos; ++i)
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
		m_parent->removeChild(this);
	
	m_parent = parent;	
	if(parent)
		m_parent->addChild(this, pos);
}

bool Updatable::removeChild(Updatable *child)
{
	if(child->getParent() == this)
		for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
		{
			if(*it == child)
			{
				m_child.erase(it);
				child->m_parent = NULL;
				return true;
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

void Updatable::setFocusCallback(void (*focusCallback)(Updatable*, void*), void* data)
{
	m_focusCallback = focusCallback;
	m_focusDatas    = data;
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

void Updatable::setClipping(const Clipping& clip)
{
	m_clip = clip;
}

void Updatable::enableClipping(bool enable)
{
	m_enableClipping = enable;
}

const Clipping& Updatable::getClipping() const
{
	return m_clip;
}

bool Updatable::getEnableClipping() const
{
	return m_enableClipping;
}
