#include "Button.h"

Button::Button(Updatable *parent, Text &text, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active(), m_background(NULL), m_text(&text)
{
	if(rect == Rectangle3f(0, 0, 0, 0, 0, 0))
		setDefaultConf(m_text->getDefaultConf());

	m_drawables.push_back(m_text);
	m_drawables.push_back(m_background);
	m_text->setUpdateFocus(false);
	m_activeOnce = true;
	centerText();
}

Button::Button(Updatable *parent, Sprite &image, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active(), m_background(&image), m_text(NULL)
{
	if(rect == Rectangle3f(0, 0, 0, 0, 0, 0))
		setDefaultConf(m_background->getDefaultConf());
	m_drawables.push_back(m_text);
	m_drawables.push_back(m_background);
	m_background->setUpdateFocus(false);
	m_activeOnce = true;
}

Button::Button(Updatable *parent, Text &text, Sprite &image, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active(), m_background(&image), m_text(&text)
{
	if(rect == Rectangle3f(0, 0, 0, 0, 0, 0))
		setDefaultConf(m_background->getDefaultConf());
	m_drawables.push_back(m_text);
	m_drawables.push_back(m_background);
	m_text->setUpdateFocus(false);
	m_background->setUpdateFocus(false);
	centerText();
	m_activeOnce = true;
}

Button::Button(Updatable *parent, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active()
{
	m_drawables.push_back(m_text);
	m_drawables.push_back(m_background);
	m_activeOnce = true;
}

void Button::onFocus(Render &render)
{
	activeIt();
}

void Button::update(Render &render)
{
	if(!m_canUpdate)
		return;
	GroupDrawable::update(render);
}

void Button::onUpdate(Render &render)
{
	Active::update();
}

void Button::centerText()
{
	if(m_text != NULL)
	{
		m_text->setPositionOrigin(-m_text->getDefaultSize()/2.0f);
		m_text->setPosition(getDefaultSize()/2.0f);
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
