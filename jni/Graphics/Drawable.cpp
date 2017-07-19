#include "Drawable.h"
#include "nativeDrawable.h"

PFNGLBINDVERTEXARRAYOESPROC    Drawable::bindVertexArrayOES;
PFNGLDELETEVERTEXARRAYSOESPROC Drawable::deleteVertexArraysOES;
PFNGLGENVERTEXARRAYSOESPROC    Drawable::genVertexArraysOES;
PFNGLISVERTEXARRAYOESPROC      Drawable::isVertexArrayOES;

Drawable::Drawable(Updatable* parent, Material* material, const Rectangle3f& defaultConf) : GroupTransformable(defaultConf), Updatable(parent), m_material(material), m_vboID(0), m_staticToCamera(false)
{
	setMaterial(m_material);
}

Drawable::~Drawable()
{
	deleteVbos();
}

void Drawable::updateGPU(Render& render)
{
	if(!m_canDraw)
		return;

	draw(render);
	Updatable::updateGPU(render);
}

bool Drawable::testFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(!m_staticToCamera)
	{
		Rectangle3f rect = getRect(mvp);
//		if(Material::getGlobalEnableClipping())
//			return touchInRect(getRectIntersect(rect, Rectangle3f(Material::getGlobalClipping(), 0.0, 0.0)), te.pid);
		return touchInRect(rect, te.pid);
	}

	else
	{
		Rectangle3f rect = getRect(mvp*glm::inverse(render.getCamera().getMatrix()));
//		if(Material::getGlobalEnableClipping())
//			return touchInRect(getRectIntersect(rect, Rectangle3f(Material::getGlobalClipping(), 0.0, 0.0)), te.pid);
		return touchInRect(rect, te.pid);
	}
}

void Drawable::draw(Render& render, const glm::mat4& transformation)
{
	if(!m_canDraw)
		return;

	if(m_material)
		m_material->enableShader();

	glm::mat4 mvp = transformation;
	if(!m_staticToCamera)
		mvp = render.getCamera().getMatrix() * mvp;
	onDraw(render, mvp);

//	if(m_material)
//		m_material->disableShader();
}

void Drawable::moveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	for(std::vector<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); it++)
		(*it)->moveEvent(te, render, mvp);

	glm::mat4 t = mvp * getMatrix();
	if(m_staticToCamera)
		t = glm::inverse(render.getCamera().getMatrix()) * t;
	onMoveEvent(te, render, t);
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

Rectangle3f Drawable::getGlobalRect() const
{
	Rectangle3f rect = mvpToRect(getMatrix());
	if(m_child.size() > 0)
		return getRectAddiction(rect, Updatable::getGlobalRect());
	return rect;
}

glm::mat4 Drawable::preMatrix() const
{
	if(m_applyTransformation)
		return m_applyTransformation->preMatrix();

	glm::mat4 m(1.0f);
	const Updatable* p = m_parent;
	while(p != NULL)
	{
		if(p->getApplyChildrenTransformable())
			m = p->getApplyChildrenTransformable()->getMatrix() * m;
		p = p->getParent();
	}

	return m;
}
