#include "Widgets/ScrollWindow.h"

ScrollWindow::ScrollWindow(Updatable* parent, const Vector2ui& pixelSize) : Active(), RenderDrawabled(parent, &m_renderMaterial, pixelSize), m_onFocusCount(0)
{
	m_permanentActivated = true;
	setChildrenTransformable(&m_childTrans);
}

ScrollWindow::~ScrollWindow()
{}

void ScrollWindow::onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	m_oldValue   = m_value;
	m_onFocusPos = glm::vec2(mvp*glm::vec4(te.x, te.y, 0.0, 1.0));	
	activeIt();
}

void ScrollWindow::onTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(m_onFocusCount < MAX_SCROLLWINDOW_COUNT && length(m_onFocusPos - glm::vec2(mvp*glm::vec4(te.x, te.y, 0.0, 1.0))) < MAX_SCROLLWINDOW_DISTANCE)
		getRenderTexture().updateFocus(te, render, mvp);
	m_onFocusCount = 0;
	m_oldValue   = m_value;
	disactiveIt();
}

void ScrollWindow::onMoveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
//	if(isActive())
//	{
		//Don't know if it should be optimized. Try to get the interval of scrolling
		Rectangle3f myRect = getRect();
		Rectangle3f gRect = getRenderTexture().getGlobalRect();
		m_xInterval.x = gRect.x;
		m_xInterval.y = gRect.x + gRect.width;
		m_yInterval.x = gRect.y;
		m_yInterval.y = gRect.y + gRect.height;

		//Compute the movement
		float vX = -myRect.width*(te.x - m_onFocusPos.x) / 2.0f;
		float vY = -myRect.height*(te.y - m_onFocusPos.y) / 2.0f;

		//Compute the position
		m_value.x = fmin(m_oldValue.x + vX * (gRect.width-2.0f)/2.0f, (gRect.width-2.0f)/2.0f); 
		m_value.x = fmax(m_value.x, 0.0);
		m_value.y = fmin(m_oldValue.y + vY * (gRect.height-2.0f)/2.0f, (gRect.height-2.0f)/2.0f); 
		m_value.y = fmax(m_value.y, 0.0);

		LOG_ERROR("RECTX : %f RECTY : %f RECTWIDTH : %f RECTHEIGHT %f M_VALUEX : %f M_VALUEY : %f", gRect.x, gRect.y, gRect.width, gRect.height, m_value.x, m_value.y);

		//Move the camera
		getRenderTexture().getCamera().setPosition(glm::vec3(1 + gRect.x + m_value.x/2.0f, 1+gRect.y + m_value.y/2.0f, 0.0));
//	}
}

void ScrollWindow::onUpdate(Render &render)
{
	const Rectangle3f rect = getRect();
	m_clip = Rectangle2f(rect.x, rect.y, rect.width, rect.height);
	if(m_isActive)
		m_onFocusCount++;
}
