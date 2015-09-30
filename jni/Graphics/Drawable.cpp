#include "Drawable.h"

Drawable::Drawable(Updatable* parent, Material* material, const Rectangle3f& defaultConf) : Transformable(defaultConf), Updatable(parent), m_material(material), m_vboID(0), m_canDraw(true), m_setTransToChildren(false)
{
	setMaterial(m_material);
}

Drawable::~Drawable()
{
	deleteVbos();
}

void Drawable::update(Renderer& renderer)
{
	draw(renderer);
	Updatable::update(renderer);
}

void Drawable::draw(Renderer& renderer, const glm::mat4& transformation)
{
	if(!m_canDraw)
		return;

	if(m_material)
		m_material->enableShader();

	glm::mat4 mvp = getMatrix();
	if(!m_staticToCamera)
		mvp = renderer.getCamera()->getMatrix() * transformation * mvp;
	onDraw(renderer, mvp);

	if(m_material)
		m_material->disableShader();
}

void Drawable::onMove(const glm::vec3& v, bool useScale)
{
	if(m_setTransToChildren)
		for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			if(Drawable* drawableChild = dynamic_cast<Drawable*>(*it))
				drawableChild.move(v, useScale);
}

void Drawable::onRotate(float angle, const glm::vec3& axis, const glm::vec3& origin)
{
	if(m_setTransToChildren)
		for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			if(Drawable* drawableChild = dynamic_cast<Drawable*>(*it))
				drawableChild.onRotate(s);
}

void Drawable::onScale(const glm::vec3& s)
{
	if(m_setTransToChildren)
		for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			if(Drawable* drawableChild = dynamic_cast<Drawable*>(*it))
				drawableChild.scale(s);
}

void Drawable::setCanDraw(bool d)
{
	m_canDraw = d;
}

void Drawable::setMaterial(Material* material)
{
	m_material = material;
}

void Drawable::setTransToChildren(bool t)
{
	m_setTransToChildren = t;
}

void Drawable::staticToCamera(bool s)
{
	m_staticToCamera = s;
}

bool Drawable::isStaticToCamera() const
{
	return m_staticToCamera;
}

bool Drawable::getSetTransToChildren() const
{
	return m_setTransToChildren;
}

bool Drawable::canDraw() const
{
	return m_canDraw;
}

const Material* Drawable::getMaterial() const
{
	return m_material;
}

void Drawable::deleteVbos()
{
	if(glIsBuffer(m_vboID))
		glDeleteBuffers(1, &m_vboID);
}
