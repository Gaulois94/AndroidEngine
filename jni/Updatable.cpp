#include "Updatable.h"
#include "Render.h"

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
	setParent(NULL);
}

void Updatable::updateFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(!m_updateFocus || !m_canUpdate)
		return;

	for(std::list<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); ++it)
	{
		if(Updatable::focusIsCheck == true)
			return;
		(*it)->updateFocus(te, render, mvp);
	}

	if(testFocus(te, render))
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


void Updatable::moveEvent(const TouchEvent& te)
{
	for(std::list<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); it++)
		(*it)->moveEvent(te);

	onMoveEvent(te);
}

void Updatable::onMoveEvent(const TouchEvent& te)
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
	for(std::list<Updatable*>::iterator it = m_child.begin(); it!=m_child.end(); ++it)
		if(*it)
			(*it)->updateGPU(render);
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
