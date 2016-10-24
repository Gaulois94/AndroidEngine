#include "Render.h"
#include "Drawable.h"

Render::Render(Updatable* parent) : Updatable(parent), m_ambientColor(0.1, 0.1, 0.1, 1.0)
{
}

Render::~Render()
{
}

void Render::draw(Drawable& drawable, const glm::mat4& transformation)
{
	initDraw();
	drawable.draw(*this, transformation);
	stopDraw();
}

void Render::updateFocus(const TouchEvent& te, Render& render)
{
	Updatable::updateFocus(te, *this);
}

void Render::update(Render& render)
{
	Updatable::update(*this);
}

void Render::updateGPU(Render& render)
{
	initDraw();
	Updatable::updateGPU(*this);
	stopDraw();
}

Camera& Render::getCamera()
{
	return m_camera;
}

const Color& Render::getAmbientColor() const
{
	return m_ambientColor;
}

Rectangle3f Render::getRectOnScreen(const Transformable& trans) const
{
	Render* render = Updatable::getRenderParent();
	glm::mat4 mvp = m_camera.getMatrix();
	while(render != NULL)
		mvp = render->getCamera() * mvp;

	return trans.getRect(mvp);
}

glm::vec3 Render::getPositionOnScreen(const glm::vec3& p) const
{
	return glm::vec3(m_camera.getMatrix() * glm::vec4(p, 1.0));
}

Render* Render::getRenderParent()
{
	return this;
}
