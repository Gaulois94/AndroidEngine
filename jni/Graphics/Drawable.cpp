#include "Drawable.h"

Drawable::Drawable(Updatable* parent, Material* material, const Rectangle3f& defaultConf) : Transformable(defaultConf), Updatable(parent), m_material(material), m_vboID(0), m_canDraw(true), m_staticToCamera(false), m_setTransToChildren(false)
{
	setMaterial(m_material);
}

Drawable::~Drawable()
{
	deleteVbos();
}

void Drawable::update(Render& render)
{
	if(m_setTransToChildren)
	{
		//Set the camera current apply transformation.
		Camera renderCamera = render.getCamera();
		//save the old apply matrix
		glm::mat4 currentApplyTransformation = renderCamera.getApplyTransformation();
		//apply our transformation to the current one
		renderCamera.setApplyTransformation(getMatrix() * renderCamera.getApplyTransformation());

		//Call the usual update function
		draw(render);
		Updatable::update(render);

		//restore the apply transformation matrix
		renderCamera.setApplyTransformation(currentApplyTransformation);
	}
	else
	{
		draw(render);
		Updatable::update(render);
	}
}

void Drawable::updateFocus(Render& render)
{
	Updatable::updateFocus(render);
	if(!m_staticToCamera && touchInRect(render.getRectOnScreen(*this)) || (m_staticToCamera && touchInRect(getRect())))
		onFocus(render);
}

void Drawable::draw(Render& render, const glm::mat4& transformation)
{
	if(!m_canDraw)
		return;

	if(m_material)
		m_material->enableShader();

	glm::mat4 mvp = getMatrix();
	if(!m_staticToCamera)
		mvp = render.getCamera().getMatrix() * transformation * mvp;
	onDraw(render, mvp);

	if(m_material)
		m_material->disableShader();
}

void Drawable::onMove(const glm::vec3& v, bool useScale)
{
}

void Drawable::onRotate(float angle, const glm::vec3& axis, const glm::vec3& origin)
{
}

void Drawable::onScale(const glm::vec3& s)
{
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

bool Drawable::getTransToChildren() const
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
