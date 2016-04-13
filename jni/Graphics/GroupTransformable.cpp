#include "GroupTransformable.h"

GroupTransformable::GroupTransformable(const Rectangle3f& defaultConf) : Transformable(defaultConf), m_enabled(true)
{}

void GroupTransformable::addTransformable(Transformable* t)
{
	m_vectorTransformable.push_back(t);
	if(m_enabled)
		t->setApplyTransformation(this);
}

void GroupTransformable::setEnableTransformation(bool e)
{
	m_enabled = e;
	if(e)
		for(std::vector<Transformable*>::iterator it = m_vectorTransformable.begin(); it != m_vectorTransformable.end(); it++)
			(*it)->setApplyTransformation(this);
	else
		for(std::vector<Transformable*>::iterator it = m_vectorTransformable.begin(); it != m_vectorTransformable.end(); it++)
			(*it)->setApplyTransformation(NULL);
}

bool GroupTransformable::getEnableTransformation()
{
	return m_enabled;
}
