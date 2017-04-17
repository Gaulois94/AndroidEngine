#include "GroupDrawable.h"

GroupDrawable::GroupDrawable(Updatable* parent, Material* material, const Rectangle3f& defaultConf) : Drawable(parent, material, defaultConf), m_deleteAuto(false)
{
}

GroupDrawable::~GroupDrawable()
{
	if(m_deleteAuto)
		for(std::list<Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
			if((*it) != NULL)
				delete (*it);
}

void GroupDrawable::onUpdate(Render& render)
{
	for(std::list<Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
		if((*it) != NULL)
			(*it)->onUpdate(render);
}

void GroupDrawable::draw(Render& render, const glm::mat4& transformation)
{
	if(!m_canDraw)
		return;

	glm::mat4 mvp = transformation*getMatrix();

	for(std::list<Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
		if((*it))
			(*it)->draw(render, mvp);

	if(m_material)
		m_material->enableShader();

	if(m_staticToCamera)
		onDraw(render, mvp);
	else
		onDraw(render, render.getCamera().getMatrix() * mvp);

	if(m_material)
		m_material->disableShader();
}

void GroupDrawable::onDraw(Render& render, const glm::mat4& transformation)
{
}

void GroupDrawable::staticToCamera(bool s)
{
	for(std::list<Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
		if((*it) != NULL)
			(*it)->staticToCamera(s);
	Drawable::staticToCamera(s);
}

//It set all the material of the drawables
void GroupDrawable::setMaterial(Material* material)
{
	Drawable::setMaterial(material);
	for(std::list<Drawable*>::iterator it = m_drawables.begin(); it != m_drawables.end(); it++)
		if((*it) != NULL)
			(*it)->setMaterial(material);
}

std::list<Drawable*> GroupDrawable::getDrawables()
{
	return m_drawables;
}

void GroupDrawable::deleteAuto(bool del)
{
	m_deleteAuto = del;
}

void GroupDrawable::addSubDrawable(Drawable* d, int pos)
{
	d->setParent(NULL);
	if(pos < 0 || pos >= m_drawables.size())
		m_drawables.push_back(d);
	else
		m_drawables.insert(std::advance(m_drawables.begin(), pos), d);

}

void GroupDrawable::deleteSubDrawable(Drawable* d)
{
	m_drawables.remove(d);
}

void GroupDrawable::deleteSubDrawable(int pos)
{
	if(m_drawables.size() == 0)
		return;

	if(pos < 0 || pos >= m_drawables.size())
		m_drawables.erase(m_drawables.end());
	else
		m_drawables.erase(std::advance(m_drawables.begin(), pos));
}
