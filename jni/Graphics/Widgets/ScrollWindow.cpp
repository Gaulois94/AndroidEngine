#include "Widgets/ScrollWindow.h"

ScrollWindow::ScrollWindow(Updatable* parent, const Vector2ui& pixelSize) : Active(), RenderDrawabled(parent, &m_renderMaterial, pixelSize), m_onFocusCount(0)
{
	m_permanentActivated = true;
	setChildrenTransformable(&m_childTrans);
}

ScrollWindow::~ScrollWindow()
{}

void ScrollWindow::updateFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(testFocus(te, render, mvp))
	{
		onFocus(te, render, mvp);
		Updatable::objectFocused = this;
		Updatable::focusIsCheck = true;
		return;
	}

	RenderDrawabled::updateFocus(te, render, mvp);
}

void ScrollWindow::onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	m_oldValue   = m_value;
	m_onFocusPos = glm::vec2(te.x, te.y);	
	activeIt();
}

void ScrollWindow::onTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(m_onFocusCount < MAX_SCROLLWINDOW_COUNT && length(m_onFocusPos - glm::vec2(te.x, te.y)) < MAX_SCROLLWINDOW_DISTANCE)
		getChangeMvp().updateFocus(te, render, mvp);
	m_onFocusCount = 0;
	m_oldValue   = m_value;
	disactiveIt();
}

void ScrollWindow::onMoveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(isActive())
	{
		//Don't know if it should be optimized. Try to get the interval of scrolling
		Rectangle3f myRect = getRect();
		Rectangle3f gRect = getRenderTexture().getGlobalRect();
		m_xInterval.x = gRect.x;
		m_xInterval.y = gRect.x + gRect.width;
		m_yInterval.x = gRect.y;
		m_yInterval.y = gRect.y + gRect.height;

		//Compute the movement
		float vX = -(te.x - m_onFocusPos.x) / myRect.width;
		float vY = -(te.y - m_onFocusPos.y) / myRect.height;

		//Compute the position
		m_value.x = fmin(m_oldValue.x + vX * (gRect.width-2.0f), (gRect.width-2.0f)); 
		m_value.x = fmax(m_value.x, 0.0);
		m_value.y = fmin(m_oldValue.y + vY * (gRect.height-2.0f), (gRect.height-2.0f)); 
		m_value.y = fmax(m_value.y, 0.0);

		//Move the camera
		getRenderTexture().getCamera().setPosition(glm::vec3(1 + gRect.x + m_value.x, 1+gRect.y + m_value.y, 0.0));
	}
}

void ScrollWindow::onUpdate(Render &render)
{
	const Rectangle3f rect = getRect();
	m_clip = Rectangle2f(rect.x, rect.y, rect.width, rect.height);
	if(m_isActive)
		m_onFocusCount++;
}
