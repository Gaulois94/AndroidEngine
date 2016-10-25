#include "Widgets/Slider.h"

Slider::Slider(Updatable *parent, Material* backgroundMaterial, Material* cursorMaterial, uint32_t valueMin, uint32_t valueMax, const Orientation& position, int pourcentageGlobalRectangle) : 
	Drawable(parent, NULL, Rectangle3f(0.0, 0.0, 0.0, 1.0, 1.0, 0.0)), Active(), m_background(NULL, backgroundMaterial), m_cursorRectangle(NULL, cursorMaterial), m_cursor(this, (Drawable&)m_cursorRectangle), 
	m_minValue(valueMin), m_maxValue(valueMax), m_orientation(position), m_pourcentageGlobalRectangle(pourcentageGlobalRectangle)
{
	m_cursor.setActiveOnce(false);
	m_cursor.setCanDraw(false);
	m_cursor.setPosition(glm::vec3(0.0, 0.0, 0.0));
	m_permanentActivated = true;

	if(m_orientation == VERTICAL)
		m_cursor.setScale(glm::vec3(pourcentageGlobalRectangle / 100.0f, 1.0, 1.0));
	else
		m_cursor.setScale(glm::vec3(pourcentageGlobalRectangle / 100.0f, 1.0, 1.0));
}

Slider::~Slider()
{}

void Slider::onUpdate(Render& render)
{
	if(m_hasStartMoving && !m_cursor.isActive())
		m_hasStartMoving = false;
}

void Slider::onDraw(Render& render, const glm::mat4& mvp)
{
	//Update here because need the mvp to take in consideration the movement
	m_cursor.draw(render, mvp);
	if(m_cursor.isActive())
	{
		Rectangle3f rect = mvpToRect(mvp);
        float v;

        if(m_orientation == VERTICAL)
            v = (m_touchCoord.y - m_touchCoord.startY) / rect.height;
        else
            v = (m_touchCoord.x - m_touchCoord.startX) / rect.width;

        m_value = fmin(m_lastValue + v, m_maxValue);
        m_value = fmax(m_value, m_minValue);

        updateCursorPosition();
	}
	m_background.draw(render, mvp);
}

void Slider::onMove(const TouchEvent& te)
{
	const TouchCoord* tc = getTouchCoord(te.pid);
	if(tc && m_cursor.isActive())
	{
		m_touchCoord     = *tc;
		if(!m_hasStartMoving)
		{	
			m_oldCoord       = m_touchCoord;
			m_lastValue      = m_value;
		}
		m_hasStartMoving = true;
	}
}

void Slider::setOrientation(const Orientation& orientation)
{
    m_orientation = orientation;
}

float Slider::getValue() const
{
    return m_value;
}

void Slider::updateCursorPosition()
{
    if(m_orientation == HORIZONTAL)
        m_cursor.setPosition(glm::vec3((1.0f-getScale().x)/(m_maxValue - m_minValue), 0.0, 0.0));
    else
        m_cursor.setPosition(glm::vec3(0.0, (1.0f-getScale().y)/(m_maxValue - m_minValue), 0.0));
}

bool Slider::howActive()
{
	return m_cursor.isActive();
}

bool Slider::howDisactive()
{
	return !m_cursor.isActive();
}

bool Slider::howSelect()
{
	return m_cursor.isSelect();
}

bool Slider::howDeselect()
{
	return !m_cursor.isSelect();
}
