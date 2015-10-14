#include "GroupDrawable.h"

GroupDrawable::GroupDrawable(Updatable* parent, Material* material, const Rectangle3f& defaultConf) : Drawable(parent, material, defaultConf)
{}

void GroupDrawable::update(Render& render)
{
	for(std::map<std::string, Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
		it->second->update(render);
	Drawable::update(render);
}

void GroupDrawable::onDraw(Render& render, const glm::mat4& transformation)
{
	if(!m_canDraw)
		return;

	glm::mat4 mvp = getMatrix() * transformation;
	for(std::map<std::string, Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
		render.draw(*(it->second), mvp);
}

void GroupDrawable::staticToCamera(bool s)
{
	for(std::map<std::string, Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
		it->second->staticToCamera(s);
	Drawable::staticToCamera(s);
}

//It set all the material of the drawables
void GroupDrawable::setMaterial(Material* material)
{
	Drawable::setMaterial(material);
	for(std::map<std::string, Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
		it->second->setMaterial(material);
}

ResourcesManager<Drawable*> GroupDrawable::getDrawables()
{
	return m_drawables;
}
