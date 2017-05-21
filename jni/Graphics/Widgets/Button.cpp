#include "Button.h"

Button::Button(Updatable *parent, Text &text, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active(), m_background(NULL), m_text(&text)
{
	m_text->setPosition(glm::vec3(0.0, 0.0, 0.0));
	if(rect == Rectangle3f(0, 0, 0, 0, 0, 0))
		setDefaultConf(m_text->getInnerRect());

	addSubDrawable(m_text);
	m_text->setUpdateFocus(false);
	m_activeOnce = true;
	centerText();
	m_updateFocus = true;
}

Button::Button(Updatable *parent, Drawable &image, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active(), m_background(&image), m_text(NULL)
{
	m_background->setPosition(glm::vec3(0.0, 0.0, 0.0));
	if(rect == Rectangle3f(0, 0, 0, 0, 0, 0))
		setDefaultConf(m_background->getInnerRect());
	addSubDrawable(m_background);
	m_background->setUpdateFocus(false);
	m_activeOnce = true;
	m_updateFocus = true;
}

Button::Button(Updatable *parent, Text &text, Drawable &image, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active(), m_background(&image), m_text(&text)
{
	m_background->setPosition(glm::vec3(0.0, 0.0, 0.0));
	if(rect == Rectangle3f(0, 0, 0, 0, 0, 0))
		setDefaultConf(m_background->getInnerRect());

	addSubDrawable(m_background);
	addSubDrawable(m_text);
	m_text->setUpdateFocus(false);
	m_background->setUpdateFocus(false);
	centerText();
	m_activeOnce = true;
	m_updateFocus = true;
}

Button::Button(Updatable *parent, const Rectangle3f &rect) : GroupDrawable(parent, NULL, rect), Active(), m_background(NULL), m_text(NULL)
{
	m_activeOnce = true;
	m_updateFocus = true;
}

void Button::onFocus(const TouchEvent& te, Render &render, const glm::mat4& mvp)
{
	activeIt();
}

void Button::update(Render &render)
{
	Drawable::update(render);
}

void Button::onUpdate(Render &render)
{
	Drawable::onUpdate(render);
	Active::update();
}

void Button::onTouchUp(const TouchEvent& te)
{
	m_isActive = false;
}

void Button::centerText()
{
    if(m_text)
	{
		m_text->setPositionOrigin(m_text->getDefaultPos() + m_text->getDefaultSize()/2.0f, true);
		m_text->setPosition(getDefaultPos() + getDefaultSize()/2.0f);
	}
}

void Button::setBackground(Drawable &image)
{
	if(m_background)
		m_background->setParent(NULL);

	m_background = &image;

	//Reset the parent
	m_text->setParent(NULL);
	if(m_background)
	{
		m_background->setParent(this);
		m_background->setUpdateFocus(false);
		m_background->setApplyTransformation(this);
	}
	m_text->setParent(this);

	//Change the background scale
	setBackgroundScale();
}

void Button::setText(Text &string)
{
	if(m_text)
		m_text->setParent(NULL);
	m_text = &string;

	if(m_text)
	{
		m_text->setParent(this);
		m_text->setApplyTransformation(this);
		m_text->setUpdateFocus(false);
	}
	centerText();
}

const Text* Button::getText() const
{
	return m_text;
}

bool Button::hasBackground() const
{
	return (m_background != NULL);
}

bool Button::hasText() const 
{
	return (m_text != NULL);
}

void Button::setRequestSize(const glm::vec3& size, bool keepPos)
{
	setDefaultSize(size);
	setBackgroundScale();
	if(m_text)
	{
		glm::vec3 textSize = m_text->getInnerRect().getSize();

		float textScale = fmin(size.y/textSize.y, size.x/textSize.x);
		textScale = fmin(1.0, textScale);

		if(textScale < 1.0)
			m_text->scale(glm::vec3(textScale, textScale, 1.0));
	}
	centerText();
}

void Button::setBackgroundScale()
{
	if(!m_background)
		return;
	glm::vec3 backgroundDS = m_background->getDefaultSize();
	if(backgroundDS.x == 0)
		backgroundDS.x = 1.0;
	if(backgroundDS.y == 0)
		backgroundDS.y = 1.0;
	if(backgroundDS.z == 0)
		backgroundDS.z = 1.0;
	m_background->setScale(getDefaultSize() / backgroundDS);
}
