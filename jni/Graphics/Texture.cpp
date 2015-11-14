#include "Texture.h"

Texture::Texture(int width, int height, int id, const Color& maskColor) : m_width(width), m_height(height), m_id(0), m_maskColor(maskColor)
{
	if(glIsTexture(id))
		m_id = id;
	else
		Texture(width, height, maskColor);
}

Texture::Texture(int width, int height, const Color& maskColor) : m_width(width), m_height(height), m_maskColor(maskColor)
{
	int format = GL_RGBA;
	glGenTextures(1, &m_id);

	glBindTexture(GL_TEXTURE_2D, m_id);
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const unsigned char* pixels, int width, int height, bool alpha, const Color& maskColor) : m_width(width), m_height(height), m_maskColor(maskColor)
{
	int internalFormat = GL_RGBA;
	int format = GL_RGBA;
	if(!alpha)
		format = GL_RGB;

	glGenTextures(1, &m_id);

	glBindTexture(GL_TEXTURE_2D, m_id);
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const Bitmap* bmp, const Color& maskColor) : Texture(bmp->pixels, bmp->info.width, bmp->info.height, true, maskColor)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::setMaskColor(const Color& mask)
{
	m_maskColor = mask;
}

glm::vec2 Texture::pixelsToTextureDirectXCoord(const glm::vec2& pos) const
{
	return glm::vec2(pos.x, m_height-pos.y) / glm::vec2(m_width, m_height);
}

glm::vec2 Texture::pixelsToTextureCoord(const glm::vec2& pos) const
{
	return glm::vec2(pos.x, pos.y) / glm::vec2(m_width, m_height);
}

FloatRect2 Texture::getRect(const glm::vec2& pos, const glm::vec2& size) const
{
	FloatRect2 rect;
	glm::vec2 v = pixelsToTextureCoord(pos);

	rect.x = v.x;
	rect.y = v.y;
	rect.width = size.x / (float)m_width;
	rect.height = size.y / (float)m_height;

	return rect;
}

FloatRect2 Texture::getRect(const Rectangle2ui& rect) const
{
	return getRect(glm::vec2(rect.x, rect.y), glm::vec2(rect.width, rect.height));
}

FloatRect2 Texture::getDirectXRect(const glm::vec2& pos, const glm::vec2& size) const
{
	FloatRect2 rect;
	glm::vec2 v = pixelsToTextureDirectXCoord(pos+glm::vec2(0.0, size.y));

	rect.x = v.x;
	rect.y = v.y;
	rect.width = size.x / (float)m_width;
	rect.height = size.y / (float)m_height;

	return rect;
}

FloatRect2 Texture::getDirectXRect(const Rectangle2ui& rect) const
{
	return getDirectXRect(glm::vec2(rect.x, rect.y), glm::vec2(rect.width, rect.height));
}


GLuint Texture::getID() const
{
	return m_id;
}

int Texture::getWidth() const
{
	return m_width;
}

int Texture::getHeight() const
{
	return m_height;
}

Color Texture::getMaskColor() const
{
	return m_maskColor;
}

Texture* Texture::loadAndroidFile(const char* filePath)
{
	JNIEnv* jenv = JniMadeOf::jenv;
	jstring path = jenv->NewStringUTF(filePath);
	return (Texture*) Java_com_gaulois94_Graphics_Texture_loadFromFileTexture(jenv, 0, path);
}
