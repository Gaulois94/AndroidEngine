#include "Widgets/Slider.h"

Slider::Slider(Updatable *parent, Material* backgroundMaterial, Material* cursorMaterial, float valueMin, float valueMax, const Orientation& position, int pourcentageGlobalRectangle) : 
	Drawable(parent, NULL, Rectangle3f(0.0, 0.0, 0.0, 1.0, 1.0, 0.0)), m_background(this, backgroundMaterial), m_cursorRectangle(NULL, cursorMaterial), m_cursor(this, (Drawable&)m_cursorRectangle), 
	m_minValue(valueMin), m_maxValue(valueMax), m_orientation(position), m_pourcentageGlobalRectangle(pourcentageGlobalRectangle)
{
	m_cursor.setActiveOnce(false);
	m_cursor.setPosition(glm::vec3(0.0, 0.0, 0.0));

	if(m_orientation == VERTICAL)
		m_cursor.setScale(glm::vec3(1.0f ,pourcentageGlobalRectangle * 0.01f, 1.0f));
	else
		m_cursor.setScale(glm::vec3(pourcentageGlobalRectangle * 0.01f, 1.0f, 1.0f));

	m_cursor.setApplyTransformation(this);
	m_background.setApplyTransformation(this);
}

Slider::~Slider()
{}

void Slider::onUpdate(Render& render)
{
	Drawable::onUpdate(render);

	if(m_hasStartMoving && !m_cursor.isActive())
		m_hasStartMoving = false;
}

void Slider::draw(Render& render, const glm::mat4& mvp)
{
	Drawable::draw(render, mvp);
}

void Slider::onDraw(Render& render, const glm::mat4& mvp)
{
}

void Slider::onMoveEvent(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	if(m_cursor.isActive())
	{
		if(!m_hasStartMoving)
		{
			m_oldCoord       = glm::vec4(te.x, te.y, 0.0f, 1.0f);
			m_hasStartMoving = true;
		}

		Rectangle3f rect = mvpToRect(mvp);

		if(rect.width != 0 && rect.height != 0)
		{
			float v;
			if(m_orientation == VERTICAL)
				v = (te.y - rect.y) / rect.height;
			else
				v = (te.x - rect.x) / rect.width;

			m_value = fmin(m_minValue + v * m_maxValue, m_maxValue);
			m_value = fmax(m_value, m_minValue);

			updateCursorPosition();
			LOG_ERROR("TC X : %f, TC Y : %f, RECT X %f RECT Y %f RECT WIDTH %f RECT HEIGHT %fDEFAULTSIZE X %f", te.x, te.y, rect.x, rect.y, rect.width, rect.height, m_defaultSize.x);
		}

	}
	else
		m_hasStartMoving = true;
}

void Slider::setOrientation(const Orientation& orientation)
{
    m_orientation = orientation;
}

float Slider::getValue() const
{
    return m_value;
}

void Slider::setLimits(float valueMin, float valueMax)
{
	m_minValue = valueMin;
	m_maxValue = valueMax;
}

void Slider::setValue(float value)
{
	m_value = fmin(value, m_maxValue);
	m_value = fmax(m_value, m_minValue);
	updateCursorPosition();

}

void Slider::updateCursorPosition()
{
    if(m_orientation == HORIZONTAL)
        m_cursor.setPosition(glm::vec3((m_value-m_minValue) / m_maxValue * (1-m_pourcentageGlobalRectangle*0.01f), 0.0, 0.0));
    else
        m_cursor.setPosition(glm::vec3(0.0f, (m_value-m_minValue) / m_maxValue * (1-m_pourcentageGlobalRectangle*0.01f), 0.0));
}
