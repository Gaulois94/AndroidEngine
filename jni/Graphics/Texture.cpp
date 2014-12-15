#include "Texture.h"

Texture::Texture(int width, int height) : m_width(width), m_height(height)
{
	int format = GL_RGBA;
	glGenTexture(1, id);
	m_id = id[0];

	glBindTexture(GL_TEXTURE_2D, m_id);
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(float[] pixels, int width, int height, bool alpha) : m_width(width), m_height(height)
{
	int internalFormat = GL_RGBA;
	int format = GL_RGBA;
	if(!alpha)
		format = GL_RGB;

	int* id;
	glGenTexture(1, id);
	m_id = id[0];

	glBindTexture(GL_TEXTURE_2D, m_id);
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

Texture::Texture(const Bitmap* bmp)
{
	Texture(bmp->pixels, bmp->info.width, bmp->info.height);
}

Texture::~Texture()
{

}

int Texture::getID()
{
	return m_id;
}

int Texture::getWidth()
{
	return m_width;
}

int Texture::getHeight()
{
	return m_height;
}
