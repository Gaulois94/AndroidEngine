#include "TextEntry.h"

TextEntry::TextEntry(Updatable* parent, Material*textMaterial, const Font* font, const std::string& defaultText, Material* backgroundMaterial, Material* cursorMaterial, Material* firstTextMaterial) : Drawable(parent, NULL), TextInterface(font, defaultText.c_str()), m_textMaterial(textMaterial), m_rectangle(NULL, backgroundMaterial), m_textDrawable(NULL, (firstTextMaterial) ? firstTextMaterial : textMaterial, font, defaultText.c_str()), m_cursorMaterial(cursorMaterial), m_cursor(NULL, m_cursorMaterial)
{
	setDefaultConf(m_rectangle.getDefaultConf());
	if(m_cursorMaterial == NULL)
	{
		m_cursorMaterial = m_textMaterial;
		m_cursor.setMaterial(m_cursorMaterial);
	}
	m_cursor.setScale(glm::vec3(1.0f/CURSOR_SCALE, 1.0, 0.0));
	m_cursor.setUpdateFocus(false);
}

void TextEntry::onUpdate(Render& render)
{
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

	m_textDrawable.getMaterial()->enableClipping(clip);
	m_textDrawable.draw(render, mvp);
	m_textDrawable.getMaterial()->disableClipping();

	if(m_isWriting)
	{
		if(Updatable::objectFocused != this)
		{
			m_cursorAnim = 0;
			m_showCursor = true;
			m_isWriting  = false;
		}

		else
		{
			m_cursorAnim++;
			if(m_cursorAnim == CURSOR_ANIM)
			{
				m_cursorAnim = 0;
				m_showCursor = !m_showCursor;
			}
		}
	}

	else
		m_showCursor = false;

	if(m_isWriting && m_showCursor)
		m_cursor.draw(render, mvp);
}

void TextEntry::onFocus(const TouchEvent& te, Render& render)
{
	m_isWriting = true;
	Updatable::onFocus(te, render);
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

		//Update the cursor position
		
		//BACKSPACE
		if(key == '\b' && m_cursorPosition > 0)
			m_cursorPosition--;

		else if(key >= ' ' && key <= '~')
			m_cursorPosition++;

		updateTextPosition();
		return true;
	}
	return false;
}

void TextEntry::updateTextPosition()
{
	glm::vec2 charPos = m_textDrawable.getCharPosition(m_cursorPosition);
	glm::vec3 textPos = m_textDrawable.getPosition();
	Rectangle3f rect = m_rectangle.getRect();

	if(charPos.x < -textPos.x)
		m_textDrawable.setPosition(glm::vec3(charPos.x, textPos.y, 0.0), false);

	else if(charPos.x > textPos.x + rect.width-1.0/CURSOR_SCALE)
		m_textDrawable.setPosition(glm::vec3(-charPos.x + rect.width-1.0/CURSOR_SCALE, textPos.y, 0.0), false);

	m_cursor.setPosition((glm::vec3(charPos, 0.0) + m_textDrawable.getPosition())*glm::vec3(CURSOR_SCALE, 1, 1), true);
}

void TextEntry::setFont(const Font* font)
{
	TextInterface::setFont(font);
	m_textDrawable.setFont(font);
}

void TextEntry::setText(const char* text)
{
	TextInterface::setText(text);
	m_textDrawable.setText(text);
}

void TextEntry::setBackgroundScale(const glm::vec3& scale)
{
	m_rectangle.setScale(scale);
}

void TextEntry::setTextScale(const glm::vec3& scale)
{
	m_textDrawable.setScale(scale);
	m_cursor.setScale(scale*glm::vec3(1.0f/CURSOR_SCALE, 1.0, 0.0));
}

const Rectangle& TextEntry::getBackground() const
{
	return m_rectangle;
}

const Text& TextEntry::getTextDrawable() const
{
	return m_textDrawable;
}

void TextEntry::setResquestSize(const glm::vec3& size, bool keepPos)
{
	m_rectangle.setScale(size);
	setDefaultSize(glm::vec3(size.x, size.y, 0.0));
}
