#include "Texture.h"

Texture::Texture(int width, int height) : m_width(width), m_height(height)
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

Texture::Texture(const unsigned char* pixels, int width, int height, bool alpha) : m_width(width), m_height(height)
{
	int internalFormat = GL_RGBA;
	int format = GL_RGBA;
	if(!alpha)
		format = GL_RGB;

	glGenTextures(1, &m_id);

	glBindTexture(GL_TEXTURE_2D, m_id);
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const Bitmap* bmp) : Texture(bmp->pixels, bmp->info.width, bmp->info.height, true)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

glm::vec2 Texture::pixelsToTextureCoord(const glm::vec2& pos) const
{
	return glm::vec2(pos.x, m_height-pos.y) / glm::vec2(m_width, m_height);
}

FloatRect2 Texture::getRect(const glm::vec2& pos, const glm::vec2& size) const
{
	FloatRect2 rect;
	glm::vec2 v = pixelsToTextureCoord(pos);

	rect.x = v.x;
	rect.y = v.y - size.x / (float)m_height;
	rect.width = size.x / (float)m_width;
	rect.height = size.y / (float)m_height;

	return rect;
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
