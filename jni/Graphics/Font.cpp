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

FloatRect2 Font::getCharRect(char character) const
{
	//The texture font letter is in directX norme. Remember that the position of a text in the font is given at the baseline of the text, that's why we subtract that position with the top position (which is negative, that's why we do + and not -)
	return FloatRect2(getPosition(character)+glm::vec2(0.0, m_fontMetrics.top),
					  getSize(character));

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

Font* Font::fontFromAssets(const std::string path, uint32_t padX, uint32_t padY, uint32_t size)
{
	JNIEnv* jenv      = JniMadeOf::jenv;
	jclass fontClass  = jenv->FindClass("com/gaulois94/Graphics/Font");
	jmethodID initPtr = jenv->GetStaticMethodID(fontClass, "initPtr", "(Ljava/lang/String;III)J");
	jstring p         = jenv->NewStringUTF(path.c_str());
	long f            = jenv->CallStaticLongMethod(fontClass, initPtr, p, padX, padY, size);
	return (Font*)f;
}
