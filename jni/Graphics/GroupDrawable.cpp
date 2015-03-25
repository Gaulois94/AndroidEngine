#include "GroupDrawable.h"

GroupDrawable::GroupDrawable(Material* material) : Drawable(material)
{}

void GroupDrawable::onDraw(Renderer* renderer, glm::mat4& mvp)
{
	for(std::map<std::string, Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
		it->second->draw(renderer, mvp);
}

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
