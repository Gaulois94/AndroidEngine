#include "Updatable.h"

Updatable::Updatable(Updatable *parent) : m_parent(NULL)
{
	if(parent)
		parent->addChild(this);
}

Updatable::~Updatable()
{
	if(m_parent)
		m_parent->removeChild(this);

	for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
	{
		if(*it)
			delete (*it);
		it = m_child.erase(it);
	}
}

void Updatable::update(Renderer &render)
{
	for(std::list<Updatable*>::iterator it = m_child.begin(); it!=m_child.end(); ++it)
		if(*it)
			(*it)->update(render);
}

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

const Updatable* Updatable::getParent() const
{
	return m_parent;
}
