#include "Widgets/ScrollWidget.h"

ScrollWidget::ScrollWidget(Updatable* parent, const Rectangle2f& maxBound, const Rectangle3f& defConf) : Active(), Drawable(parent, NULL, defConf), m_onFocusCount(0), m_value(0, 0), m_oldValue(m_value), m_maxBound(maxBound)
{
	setMaxBound(m_maxBound);
	m_permanentActivated = true;
	setChildrenTransformable(&m_childTrans);
	m_enableClipping = true;
}

ScrollWidget::~ScrollWidget()
{}

void ScrollWidget::updateFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(!m_activeScroll)
		Drawable::updateFocus(te, render, mvp);
	else
	{
		if(!m_updateFocus || !m_canUpdate)
			return;

		if(testFocus(te, render, mvp))
		{
			onFocus(te, render, mvp);
			Updatable::objectFocused = this;
			Updatable::focusIsCheck = true;
			return;
		}
		else
			disactiveIt();

		if(!m_enableClipping)
			Drawable::updateFocus(te, render, mvp);
	}
}

void ScrollWidget::onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	m_oldValue   = m_value;
	m_onFocusPos = glm::vec2(te.x, te.y);	
	if(m_activeScroll)
		activeIt();
}

void ScrollWidget::updateGPU(Render& r)
{
	if(m_enableClipping)
	{
		Rectangle3f globalRect = getRect();
		m_clip                 = Rectangle2f(globalRect.x, globalRect.y, globalRect.width, globalRect.height);
	}

	Updatable::updateGPU(r);
}

void ScrollWidget::onTouchUp(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(m_activeScroll)
	{
		if(m_onFocusCount < MAX_SCROLLWINDOW_COUNT && length(m_onFocusPos - glm::vec2(te.x, te.y)) < MAX_SCROLLWINDOW_DISTANCE)
			Updatable::updateFocus(te, render, mvp);
		m_onFocusCount = 0;
		m_oldValue     = m_value;
		disactiveIt();
	}
}

void ScrollWidget::onMoveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(m_activeScroll && isActive())
	{
		Rectangle3f gRect = getDefaultConf();

		//Compute the movement
		float vX = -(te.x - m_onFocusPos.x);
		float vY = -(te.y - m_onFocusPos.y);

		//Compute the position
		if(m_axis == X_AXIS || m_axis == XY_AXIS)
		{
			m_value.x = fmax(m_oldValue.x + vX, m_maxBound.x); 
			m_value.x = fmin(m_value.x, m_maxBound.x - gRect.width + m_maxBound.width);
		}
		if(m_axis == Y_AXIS || m_axis == XY_AXIS)
		{
			m_value.y = fmax(m_oldValue.y + vY, m_maxBound.y); 
			m_value.y = fmin(m_value.y, m_maxBound.y - gRect.height + m_maxBound.height);
		}

		//Set the clip
		m_childTrans.setPosition(glm::vec3(m_value.x, m_value.y, 0));
	}
}

void ScrollWidget::setMaxBound(const Rectangle2f& r)
{
	m_maxBound = r;
	Rectangle3f gRect = getDefaultConf();

	if(m_axis == X_AXIS || m_axis == XY_AXIS)
	{
		m_value.x = fmax(m_value.x, m_maxBound.x); 
		m_value.x = fmin(m_value.x, m_maxBound.x - gRect.width + m_maxBound.width);
	}
	if(m_axis == Y_AXIS || m_axis == XY_AXIS)
	{
		m_value.y = fmax(m_value.y, m_maxBound.y); 
		m_value.y = fmin(m_value.y, m_maxBound.y - gRect.height + m_maxBound.height);
	}

	m_childTrans.setPosition(glm::vec3(m_value.x, m_value.y, 0));
}

void ScrollWidget::setMoveValue(const Vector2f& mv)
{
	m_value = mv;
	setMaxBound(m_maxBound);
}

void ScrollWidget::onUpdate(Render &render)
{
	if(m_isActive && m_onFocusCount < MAX_SCROLLWINDOW_COUNT)
		m_onFocusCount++;
}
