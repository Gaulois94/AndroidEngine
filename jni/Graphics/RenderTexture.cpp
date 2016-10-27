#include "RenderTexture.h"

RenderTexture::RenderTexture(Updatable* parent, const Vector2f& size) : Render(parent)
{
	//Create the framebuffer
	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	{

		//Define the color texture
		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		{
			glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

			// Poor filtering. Needed !
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		//Don't forget to bind these textures
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);

		/*
		//Define the depth texture
		GLuint depthrenderbuffer;
		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		{
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
		}
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
		*/

		//Create the Texture object
		m_texture = new Texture(size.x, size.y, textureID);
//		GLenum c = GL_COLOR_ATTACHMENT0;
//		glDrawBuffersEXT(1, &c);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOG_ERROR("MERDE %d", glCheckFramebufferStatus(GL_FRAMEBUFFER));
	else
		LOG_ERROR("YEAH !");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTexture::~RenderTexture()
{
	glDeleteFramebuffers(1, &m_frameBuffer);
	delete m_texture;
}

void RenderTexture::display()
{
	//Do nothing : all the draw calls modify directly the framebuffer and its texture (no swap buffer)
}

void RenderTexture::initDraw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glViewport(0, 0, m_texture->getWidth(), m_texture->getHeight());
}

void RenderTexture::stopDraw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::clear()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const Texture* RenderTexture::getTexture() const
{
	return m_texture;
}
