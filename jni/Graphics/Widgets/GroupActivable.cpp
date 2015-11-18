#include "GroupActivable.h"

GroupActivable::GroupActivable() : m_currentActive(NULL), m_onChange(NULL)
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
	active->setOnChangeFunc(GroupActivable::changeActive, (void*)this);
	active->setActiveOnce(false);
}

changeFunc_t GroupActivable::getOnChangeFunc()
{
	return m_onChange;
}

void* GroupActivable::getOnChangeParam()
{
	return m_param;
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
	if(grp->getOnChangeFunc())
		grp->getOnChangeFunc()(act, grp->getOnChangeParam());
}
