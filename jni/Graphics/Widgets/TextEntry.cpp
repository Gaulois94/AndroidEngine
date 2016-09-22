#include "TextEntry.h"

TextEntry::TextEntry(Updatable* parent, Material*textMaterial, const Font* font, const std::string& defaultText, Material* backgroundMaterial, Material* firstTextMaterial) : Drawable(parent, NULL), TextInterface(font, defaultText.c_str()), m_textMaterial(textMaterial), m_rectangle(NULL, backgroundMaterial), m_text(NULL, (firstTextMaterial) ? firstTextMaterial : textMaterial, font, defaultText.c_str())
{
	setDefaultConf(m_rectangle.getDefaultConf());
}

void TextEntry::onDraw(Render& render, const glm::mat4& mvp)
{
	m_rectangle.draw(render, mvp);

	Rectangle3f rect = m_rectangle.getRect(glm::mat4(1.0f));

	Clipping clip;
	clip.x      = rect.x;
	clip.y      = rect.y;
	clip.width  = rect.width;
	clip.height = rect.height;

	m_text.getMaterial()->enableClipping(clip);
	m_text.draw(render, mvp);
	m_text.getMaterial()->disableClipping();
}

void TextEntry::onFocus(uint32_t pointerEvent, Render& render)
{
	Updatable::onFocus(pointerEvent, render);
	if(!m_firstFocus)
	{
		m_firstFocus = true;
		setText("");
	}
	Keyboard::showKeyboard(true);
}

bool TextEntry::onKeyDown(int32_t key)
{
	LOG_ERROR("C : %d", key);
	if(Updatable::objectFocused == this)
	{
		addChar((uint8_t)key);
		return true;
	}
	return false;
}

void TextEntry::setFont(const Font* font)
{
	TextInterface::setFont(font);
	m_text.setFont(font);
}

void TextEntry::setText(const char* text)
{
	TextInterface::setText(text);
	m_text.setText(text);
}

void TextEntry::setBackgroundScale(const glm::vec3& scale)
{
	m_rectangle.setScale(scale);
}

void TextEntry::setTextScale(const glm::vec3& scale)
{
	m_text.setScale(scale);
}

const Rectangle& TextEntry::getBackground() const
{
	return m_rectangle;
}

const Text& TextEntry::getTextDrawable() const
{
	return m_text;
}

void TextEntry::setResquestSize(const glm::vec3& size, bool keepPos)
{
	m_rectangle.setScale(size);
	setDefaultSize(glm::vec3(size.x, size.y, 0.0));
}
