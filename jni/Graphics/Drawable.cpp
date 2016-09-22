#include "Drawable.h"
#include "nativeDrawable.h"

Drawable::Drawable(Updatable* parent, Material* material, const Rectangle3f& defaultConf) : GroupTransformable(defaultConf), Updatable(parent), m_material(material), m_vboID(0), m_canDraw(true), m_staticToCamera(false)
{
	setMaterial(m_material);
}

Drawable::~Drawable()
{
	deleteVbos();
}

void Drawable::updateGPU(Render& render)
{
	if(!m_canUpdate || !m_canDraw)
		return;
	draw(render);
	Updatable::updateGPU(render);
}

bool Drawable::testFocus(uint32_t indicePointer, Render& render)
{
	return (!m_staticToCamera && touchInRect(render.getRectOnScreen(*this), indicePointer) || (m_staticToCamera && touchInRect(getRect(), indicePointer)));
}

void Drawable::draw(Render& render, const glm::mat4& transformation)
{
	if(!m_canDraw)
		return;

	if(m_material)
		m_material->enableShader();

	glm::mat4 mvp = transformation * getMatrix();
	if(!m_staticToCamera)
		mvp = render.getCamera().getMatrix() * mvp;
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

Material* Drawable::getMaterial()
{
	return m_material;
}

void Drawable::deleteVbos()
{
	if(glIsBuffer(m_vboID))
		glDeleteBuffers(1, &m_vboID);
	m_vboID = 0;
}

void Drawable::initShaders()
{
	Java_com_gaulois94_Graphics_Drawable_loadShadersDrawable(JniMadeOf::jenv, 0, JniMadeOf::context);
}
