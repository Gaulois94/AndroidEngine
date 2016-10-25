#include "RenderTexture.h"

RenderTexture::RenderTexture(Updatable* parent, const Vector2f& size) : Render(parent)
{

	GLuint m_frameBuffer;
	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	{
		//Define the color texture
		GLuint textureID;
		glGenTextures(1, textureID);
		glBindTexture(GL_TEXTURE_2D, &textureID);
		{
			glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, size.x, size.y, 0,GL_RGBA, GL_UNSIGNED_BYTE, 0);

			// Poor filtering. Needed !
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		//Define the depth texture
		GLuint depthrenderbuffer;
		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		{
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
		}
		glBindRenderbuffer(GL_RENDERBUFFER, 0);


		//Don't forget to bind these textures
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureID, 0);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_texture = new Texture(size.x, size.y, textureID);
}

void RenderTexture::display()
{
	//Do nothing : all the draw calls modify directly the framebuffer and its texture (no swap buffer)
}

void RenderTexture::initDraw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
}

void RenderTexture::stopDraw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

const Texture* RenderTexture::getTexture() const
{
	return m_texture;
}
