#include "Render.h"
#include "Drawable.h"

Render::Render(){}

void Render::draw(Drawable& drawable, const glm::mat4& transformation)
{
	initDraw();
	drawable.draw(this, transformation);
	stopDraw();
}

Camera& Render::getCamera()
{
	return m_camera;
}
