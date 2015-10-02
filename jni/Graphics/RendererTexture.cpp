#include "RendererTexture.h"

RendererTexture::RendererTexture(int width, int height) : m_texture->NULL);
{
	GLuint textureID;
	glGenTexture(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID;
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	Texture* m_texture = new Texture(width, height, textureID);

	glGenFramebuffers(1, &m_framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
	{
		//m_texture->is now GL_COLOR_ATTACHMENT0
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture->getID(), 0);
		//All the draw function will draw to the GL_COLOR_ATTACHMENT0 (thus m_texture->
		GLenum drawBuffer[] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffer(1, drawBuffer);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

~RendererTexture()
{
	glDeleteRenderbuffers(GL_FRAMEBUFFER, m_framebufferID);
}

void RendererTexture::display()
{
	stopDraw();
}

void RendererTexture::initDraw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
}

void RendererTexture::stopDraw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RendererTexture::clear()
{
	initDraw();
	glClear(GL_COLOR_BUFFER_BIT);
	stopDraw();
}
