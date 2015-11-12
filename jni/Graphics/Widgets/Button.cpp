#include "Button.h"

Button::Button(Updatable *parent, Text &text, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active(), m_background(NULL), m_text(&text)
{
	if(rect == Rectangle3f(0, 0, 0, 0, 0, 0))
		setDefaultConf(m_text->getDefaultConf());

	m_drawables.push_back(m_text);
	m_drawables.push_back(m_background);
	m_text->setParent(NULL);
	m_activeOnce = true;
	centerText();
	m_updateFocus = true;
}

Button::Button(Updatable *parent, Sprite &image, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active(), m_background(&image), m_text(NULL)
{
	if(rect == Rectangle3f(0, 0, 0, 0, 0, 0))
		setDefaultConf(m_background->getDefaultConf());
	m_drawables.push_back(m_text);
	m_drawables.push_back(m_background);
	m_background->setParent(NULL);
	m_activeOnce = true;
	m_updateFocus = true;
}

Button::Button(Updatable *parent, Text &text, Sprite &image, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active(), m_background(&image), m_text(&text)
{
	if(rect == Rectangle3f(0, 0, 0, 0, 0, 0))
		setDefaultConf(m_background->getDefaultConf());
	m_drawables.push_back(m_text);
	m_drawables.push_back(m_background);
	m_background->setParent(NULL);
	m_text->setParent(NULL);
	centerText();
	m_activeOnce = true;
	m_updateFocus = true;
}

Button::Button(Updatable *parent, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active(), m_text(NULL), m_background(NULL)
{
	m_drawables.push_back(m_text);
	m_drawables.push_back(m_background);
	m_activeOnce = true;
	m_updateFocus = true;
}

void Button::onFocus(uint32_t indicePointer, Render &render)
{
	activeIt();
}

void Button::update(Render &render)
{
	GroupDrawable::update(render);
}

void Button::onUpdate(Render &render)
{
	GroupDrawable::onUpdate(render);
	Active::update();
}

void Button::centerText()
{
    if(m_text != NULL)
	{
		m_text->setPositionOrigin(m_text->getDefaultPos() + m_text->getDefaultSize()/2.0f, true);
		m_text->setPosition(getDefaultPos() + getDefaultSize()/2.0f);
	}
}

void Button::setBackground(Sprite &image)
{
	m_background = &image;
	m_background->setUpdateFocus(false);
}

void Button::setText(Text &string)
{
	m_text = &string;
	m_text->setUpdateFocus(false);
	centerText();
}

const Text* Button::getText() const
{
	return m_text;
}

bool Button::hasSprite() const
{
	return (m_background != NULL);
}

bool Button::hasText() const 
{
	return (m_text != NULL);
}
