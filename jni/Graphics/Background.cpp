#include "Background.h"

Background::Background(Updatable* parent, Drawable* theDrawable, Drawable* background) : GroupDrawable(parent, NULL), m_drawables(theDrawable), m_background(background), m_changeCallback(Background::changeDrawableRect, (void*)this)
{
	if(m_drawables)
	{
		m_drawables->setPosition(glm::vec3(0.0, 0.0, 0.0) - m_drawables->getDefaultPos());
		m_drawables->setChangeCallback(&m_changeCallback);
		if(m_background)
			addSubDrawable(m_background);
		addSubDrawable(m_drawables);
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
	if(m_drawables)
	{
		//Else we would had have a loop function....
		m_drawables->setChangeCallback(NULL);
		setDefaultSize(m_drawables->getInnerRect().getSize());
		m_drawables->setPosition(glm::vec3(0.0, 0.0, 0.0) - m_drawables->getDefaultPos());
	}

	if(m_background && m_drawables)
	{
		m_background->setPosition(glm::vec3(0.0, 0.0, 0.0));
		m_background->setRequestSize(getDefaultSize());
	}

	if(m_drawables)
		m_drawables->setChangeCallback(&m_changeCallback);
}
