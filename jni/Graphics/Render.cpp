#include "Render.h"
#include "Drawable.h"

Render::Render() : m_ambientColor(0.0, 0.0, 0.0, 1.0)
{}

void Render::draw(Drawable& drawable, const glm::mat4& transformation)
{
	initDraw();
	drawable.draw(*this, transformation);
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
