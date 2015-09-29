#include "Drawable.h"

Drawable::Drawable(Material* material) : Transformable(), m_material(material), m_vboID(0), m_canDraw(true)
{
	setMaterial(m_material);
}

Drawable::~Drawable()
{
	deleteVbos();
}

void Drawable::update(Renderer* renderer)
{
	draw(renderer);
	Updatable::update(renderer);
}

void Drawable::draw(Renderer* renderer, const glm::mat4& transformation)
{
	if(!m_canDraw)
		return;

	if(m_material)
		m_material->enableShader();

	glm::mat4 mvp = getMatrix();
	if(!m_staticToCamera)
		mvp = renderer->getCamera()->getMatrix() * transformation * mvp;
	onDraw(renderer, mvp);

	if(m_material)
		m_material->disableShader();
}

void Drawable::setCanDraw(bool d)
{
	m_canDraw = d;
}

void Drawable::setMaterial(Material* material)
{
	m_material = material;
}

void Drawable::staticToCamera(bool s)
{
	m_staticToCamera = s;
}

bool Drawable::isStaticToCamera() const
{
	return m_staticToCamera;
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
