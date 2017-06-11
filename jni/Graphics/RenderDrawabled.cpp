#include "RenderDrawabled.h"

RenderDrawabled::RenderDrawabled(Updatable* parent, Material* mtl, const Vector2ui& pixelsSize) : Sprite(parent, mtl, NULL), m_changeMvp(this, m_trans), m_render(&m_changeMvp, pixelsSize)
{
	m_trans.setScale(glm::vec3(0.5, 0.5, 1.0));
	m_trans.setPosition(glm::vec3(0.5, 0.5, 0.0));
	m_trans.setApplyTransformation(this);

	setTexture(m_render.getTexture());
}

RenderTexture& RenderDrawabled::getRenderTexture()
{
	return m_render;
}

Updatable& RenderDrawabled::getChangeMvp()
{
	return m_changeMvp;
}

void RenderDrawabled::staticToCamera(bool s)
{
	m_changeMvp.staticToCamera(s);
	Sprite::staticToCamera(s);
}

Rectangle3f RenderDrawabled::getGlobalRect() const
{
	Rectangle3f rect = getRect();
	for(std::vector<Updatable*>::const_iterator it = m_child.begin(); it != m_child.end(); ++it)
		if((*it) != &m_render)
			rect = getRectAddiction(rect, (*it)->getGlobalRect());
	return rect;
}
