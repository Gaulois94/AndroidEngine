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
//	initDraw();
	drawable.draw(*this, transformation);
//	stopDraw();
}

void Render::updateFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	Updatable::updateFocus(te, *this, m_camera.getMatrix() * mvp);
}

void Render::moveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	Updatable::moveEvent(te, *this, m_camera.getMatrix() * mvp);
}

void Render::updateTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	Updatable::updateTouchUp(te, *this, m_camera.getMatrix()*mvp);
}

void Render::update(Render& render)
{
	Updatable::update(*this);
}

void Render::updateGPU(Render& render)
{
	bool restoreClip = false;
	Clipping saveClip;
	if(Material::getGlobalEnableClipping())
	{
		saveClip = Material::getGlobalClipping();
		Material::enableGlobalClipping(false);
		restoreClip = true;
	}

	clear();
	initDraw();
		Updatable::updateGPU(*this);
	stopDraw();
	display();

	if(restoreClip)
	{
		Material::setGlobalClipping(saveClip);
		Material::enableGlobalClipping(true);
	}
	render.initDraw();
}

Camera& Render::getCamera()
{
	return m_camera;
}

const Color& Render::getAmbientColor() const
{
	return m_ambientColor;
}

glm::vec3 Render::getPositionOnScreen(const glm::vec3& p) const
{
	return glm::vec3(m_camera.getMatrix() * glm::vec4(p, 1.0));
}

Render* Render::getRenderParent()
{
	return this;
}
