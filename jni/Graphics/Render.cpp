#include "Render.h"
#include "Drawable.h"
#include "Widgets/Alert.h"

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
	if(m_alert)
		m_alert->updateFocus(te, *this, mvp*m_camera.getMatrix());
	else
		Updatable::updateFocus(te, *this, mvp*m_camera.getMatrix());
}

bool Render::moveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(m_alert)
		return m_alert->moveEvent(te, *this, mvp*m_camera.getMatrix());
	else
		return Updatable::moveEvent(te, *this, mvp*m_camera.getMatrix());
}

void Render::updateTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(m_alert)
		m_alert->updateTouchUp(te, *this, mvp*m_camera.getMatrix());
	else
		Updatable::updateTouchUp(te, *this, mvp*m_camera.getMatrix());
}

void Render::keyDown(int32_t keyCode)
{
	if(m_alert)
		m_alert->keyDown(keyCode);
	else
		Updatable::keyDown(keyCode);	
}

void Render::keyUp(int32_t keyCode)
{
	if(m_alert)
		m_alert->keyUp(keyCode);
	else
		Updatable::keyUp(keyCode);	
}

void Render::update(Render& render)
{
	Updatable::update(*this);
	if(m_alert)
		m_alert->update(*this);
}

void Render::updateGPU(Render& render)
{
	bool restoreClip = false;
	Rectangle2f saveClip;
	if(Material::getGlobalEnableClipping())
	{
		saveClip = Material::getGlobalClipping();
		Material::enableGlobalClipping(false);
		restoreClip = true;
	}

	clear();
	initDraw();
		Updatable::updateGPU(*this);
		if(m_alert)
			m_alert->updateGPU(*this);
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

void Render::setAlert(Alert* alert)
{
	m_alert=alert;
}
