#include "Widgets/ScrollWindow.h"

ScrollWindow::ScrollWindow(Updatable* parent) : Active(), Updatable(parent), Transformable(Rectangle3f(0, 0, 0, 1, 1, 0)), m_onFocusCount(0), m_onFocusPos(), m_onMovePos()
{
	m_permanentActivated = true;
}

void ScrollWindow::onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	m_onFocusPos = glm::vec2(mvp*glm::vec4(te.x, te.y, 0.0, 1.0));	
	activeIt();
}

void ScrollWindow::onTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(m_onFocusCount < MAX_SCROLLWINDOW_COUNT && length(m_onMovePos - glm::vec2(mvp*glm::vec4(te.x, te.y, 0.0, 1.0))) < MAX_SCROLLWINDOW_DISTANCE)
		Updatable::updateFocus(te, render, mvp);
	m_onFocusCount = 0;
	disactiveIt();
}

void ScrollWindow::onMoveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	//Need to scroll the Window, look forward
}

void ScrollWindow::onUpdate(Render &render)
{
	const Rectangle3f rect = getRect();
	m_clip = Rectangle2f(rect.x, rect.y, rect.width, rect.height);
	m_onFocusCount++;
}
