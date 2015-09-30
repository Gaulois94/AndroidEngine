#include "GroupDrawable.h"

GroupDrawable::GroupDrawable(Updatable *parent, material* material) : Drawable(parent, material)
{}

void GroupDrawable::update(Renderer* renderer)
{
	for(std::map<std::string, Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
		it->second->update(renderer);
}

void GroupDrawable::draw(Renderer* renderer, glm::mat4& transformation)
{
	if(!m_canDraw)
		return;

	glm::mat4 mvp = getMatrix() * transformation;
	for(std::map<std::string, Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
		it->second->draw(renderer, mvp);
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
