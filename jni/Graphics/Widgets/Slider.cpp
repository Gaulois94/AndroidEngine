#include "Widgets/Slider.h"

Slider(Updatable *parent, Material* backgroundMaterial, Material* cursorMaterial, uint32_t valueMin, uint32_t valueMax, const Orientation& position, int pourcentageGlobalRectangle) : 
	Drawable(parent, NULL, Rectangle3f(0.0, 0.0, 0.0, 1.0, 1.0, 0.0)), Active(), m_background(NULL, backgroundMaterial), m_cursor(NULL, cursorMaterial), 
	m_minValue(valueMin), m_maxValue(valueMax), m_position(position), m_pourcentageGlobalRectangle(pourcentageGlobalRectangle)
{
	m_cursor.setActiveOnce(false);
}

Slider::~Slider()
{}

void Slider::onUpdate(Render& render)
{

}

void Slider::onDraw(Render& render, const glm::mat4& mvp)
{
	//Update here because need the mvp to take in consideration the movement
	m_cursor.draw(render, mvp);
	if(m_cursor.isActive())
	{
		Rectangle3f rect = mvpToRect(mvp);
		float x = touchCoord.x - touchCoord->startX;
		float y = touchCoord.y - touchCoord->startY;
	}
	m_background.draw(render, mvp);
}

void Slider::onMove(uint32_t pointerEvent)
{
	const TouchCoord* tc = getTouchCoord(pointerEvent);
	if(tc)
	{
		m_touchCoord = tc;
		m_oldCoord   = m_touchCoord;
	}
}

void Slider::setOrientation(const Orientation& position)
{}

float Slider::getValue() const
{}
