#include "GroupActivable.h"

GroupActivable::GroupActivable() : m_currentActive(NULL)
{}

void GroupActivable::update() 
{
	for(std::vector<Active*>::iterator it = m_vectorActive.begin(); it != m_vectorActive.end(); it++)
		if(*it)
			(*it)->update();
}

void GroupActivable::addActive(Active* active)
{
	m_vectorActive.push_back(active);
	active->setOnChangeListener(ActiveListener(GroupActivable::changeActive, (void*)this));
	active->setActiveOnce(false);
}

ActiveListener GroupActivable::getOnChangeListener()
{
	return m_onChange;
}

void GroupActivable::setActive(uint32_t i)
{
	if(i < m_vectorActive.size())
		return;
	m_vectorActive[i]->activeIt();
}

void GroupActivable::changeActive(Active* act, void* grpAct)
{
	GroupActivable* grp = (GroupActivable*)grpAct;
	grp->getOnChangeListener().fire();
}
