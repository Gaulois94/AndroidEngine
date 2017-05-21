#include "Background.h"

Background::Background(Updatable* parent, Drawable* theDrawable, Drawable* background) : GroupDrawable(parent, NULL), m_drawable(theDrawable), m_background(background), m_changeCallback(Background::changeDrawableRect, (void*)this)
{
	if(m_drawable)
	{
		m_drawable->setPosition(glm::vec3(0.0, 0.0, 0.0) - m_drawable->getDefaultPos());
		m_drawable->setChangeCallback(&m_changeCallback);
		if(m_background)
			addSubDrawable(m_background);
		addSubDrawable(m_drawable);
	}
	updateBackgroundRect();
}

void Background::changeDrawableRect(void* data)
{
	Background* self = (Background*)data;
	self->updateBackgroundRect();
}

void Background::setDrawable(Drawable* d)
{
	if(m_drawable)
		deleteSubDrawable(m_drawable);
	m_drawable = d;
	if(d)
		addSubDrawable(d);
	updateBackgroundRect();
}

void Background::setBackground(Drawable* b)
{
	if(m_background)
		deleteSubDrawable(m_background);
	m_background = b;
	if(b)
		addSubDrawable(b, 0);
	updateBackgroundRect();
}

void Background::updateBackgroundRect()
{
	if(m_drawable)
	{
		//Else we would had have a loop function....
		m_drawable->setChangeCallback(NULL);
		setDefaultSize(m_drawable->getInnerRect().getSize());
		m_drawable->setPosition(glm::vec3(0.0, 0.0, 0.0) - m_drawable->getDefaultPos());
	}

	if(m_background && m_drawable)
	{
		m_background->setPosition(glm::vec3(0.0, 0.0, 0.0));
		m_background->setRequestSize(getDefaultSize());
	}

	if(m_drawable)
		m_drawable->setChangeCallback(&m_changeCallback);
}
