#include "ChangeMvp.h"
#include "Render.h"

ChangeMvp::ChangeMvp(Updatable* parent, const Transformable& trans, bool staticToCamera) : Updatable(parent), m_trans(trans), m_staticToCamera(staticToCamera)
{
}

void ChangeMvp::updateFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	LOG_ERROR("CHANGE MVP");
	glm::mat4 m = m_trans.getMatrix();
	if(m_staticToCamera)
		m = glm::inverse(render.getCamera().getMatrix()) * m;
	Updatable::updateFocus(te, render, mvp*m);
}

bool ChangeMvp::moveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	glm::mat4 m = m_trans.getMatrix();
	if(m_staticToCamera)
		m = glm::inverse(render.getCamera().getMatrix()) * m;
	return Updatable::moveEvent(te, render, mvp*m);
}

void ChangeMvp::updateTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	LOG_ERROR("CHANGE MVP");
	glm::mat4 m = m_trans.getMatrix();
	if(m_staticToCamera)
		m = glm::inverse(render.getCamera().getMatrix()) * m;
	Updatable::updateTouchUp(te, render, mvp*m);
}

void ChangeMvp::staticToCamera(bool s)
{
	m_staticToCamera = s;
}
