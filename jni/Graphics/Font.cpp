#include "Font.h"

Font::Font(Texture* texture, int* charWidth, int* charHeight, int* posX, int* posY, int maxWidth, int maxHeight, int padX, int padY, FontMetrics& fontMetrics)
{
	for(int i=0; i < CHAR_END - CHAR_START; i++)
	{
		m_charSize.push_back(glm::vec2(charWidth[i], charHeight[i]));
		m_charPos.push_back(glm::vec2(posX[i], posY[i]));
	}

	m_maxSize = glm::vec2(maxWidth, maxHeight);
	m_pad     = glm::vec2(padX, padY);

	m_texture = texture;
	m_texture->setMaskColor(Color::TRANSPARENT);
	m_fontMetrics = fontMetrics;
}

glm::vec2 Font::getPosition(char character) const
{
	return m_charPos[character-CHAR_START];
}

glm::vec2 Font::getSize(char character) const
{
	return m_charSize[character-CHAR_START];
}

const Texture* Font::getTexture() const
{
	return m_texture;
}

float Font::getLineHeight() const
{
	return m_fontMetrics.bottom - m_fontMetrics.top;
}

const FontMetrics& Font::getFontMetrics() const
{
	return m_fontMetrics;
}
