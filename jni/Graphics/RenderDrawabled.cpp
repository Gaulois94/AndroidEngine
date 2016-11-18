#include "RenderDrawabled.h"

RenderDrawabled::RenderDrawabled(Updatable* parent, Material* mtl, const Vector2ui& pixelsSize) : Sprite(parent, mtl, NULL), m_render(this, pixelsSize), m_changeMvp(&m_render, m_trans)
{
	m_trans.setScale(glm::vec3(0.5, 0.5, 1.0));
	m_trans.setPosition(glm::vec3(0.5, 0.5, 1.0));
	m_trans.setApplyTransformation(this);

	setTexture(m_render.getTexture());
}

RenderTexture& RenderDrawabled::getRenderTexture()
{
	return m_render;
}

Updatable& RenderDrawabled::getRenderUpdatable()
{
	return m_changeMvp;
}

void RenderDrawabled::staticToCamera(bool s)
{
	m_changeMvp.staticToCamera(s);
	Drawable::staticToCamera(s);
}

Rectangle3f RenderDrawabled::getGlobalRect() const
{
	Rectangle3f rect = getRect();
	for(std::list<Updatable*>::const_iterator it = m_child.begin(); it != m_child.end(); ++it)
		if((*it) != &m_render)
			rect = getRectAddiction(rect, (*it)->getGlobalRect());
	return rect;
}
