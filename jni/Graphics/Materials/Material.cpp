#include "Materials/Material.h"

float Material::maskColor[4];

Material::Material(const Shader *shader) : m_shader(shader), m_texture(NULL), m_vboID(0), m_isUsingShader(false)
{
	if(!m_shader)
		LOG_ERROR("ERROR LOADING SHADER");
}

Material::~Material()
{
	deleteVbos();
}

void Material::enableShader()
{
	if(m_shader)
	{
		glUseProgram(m_shader->getProgramID());
		m_isUsingShader = true;
	}
}

void Material::init(Render& render, const glm::mat4& mvp, const glm::mat4& modelMatrix)
{
	if(!m_shader)
		return;
	GLint uMaskColor      = glGetUniformLocation(m_shader->getProgramID(), "uMaskColor");
	GLint uUseTexture     = glGetUniformLocation(m_shader->getProgramID(), "uUseTexture");
	GLint uTextureHandle  = glGetUniformLocation(m_shader->getProgramID(), "uTexture");
	GLint uOpacityHandle  = glGetUniformLocation(m_shader->getProgramID(), "uOpacity");
	GLint uModelMatrix    = glGetUniformLocation(m_shader->getProgramID(), "uModelMatrix");

	GLint uClippingClip   = glGetUniformLocation(m_shader->getProgramID(), "uClipping.clip");

	if(m_texture)
	{
		if(uMaskColor != -1)
		{
			m_texture->getMaskColor().getFloatArray(maskColor);
			glUniform4fv(uMaskColor, 1, maskColor);
		}
		if(uUseTexture != -1)
			glUniform1i(uUseTexture, true);
		if(uTextureHandle != -1)
			glUniform1i(uTextureHandle, 0);
	}

	else
	{
		if(uMaskColor != -1)
			glUniform4fv(uMaskColor, 1, maskColor);
		if(uUseTexture != -1)
			glUniform1i(uUseTexture, false);
		if(uTextureHandle != -1)
			glUniform1i(uTextureHandle, 0);
	}

	if(uOpacityHandle != -1)
		glUniform1f(uOpacityHandle, m_opacity);

	if(uModelMatrix != -1)
		glUniformMatrix4fv(uModelMatrix, 1, false, glm::value_ptr(modelMatrix));

	if(uClippingClip != -1)
	{
		GLint uClippingX      = glGetUniformLocation(m_shader->getProgramID(), "uClipping.x");
		GLint uClippingY      = glGetUniformLocation(m_shader->getProgramID(), "uClipping.y");
		GLint uClippingWidth  = glGetUniformLocation(m_shader->getProgramID(), "uClipping.width");
		GLint uClippingHeight = glGetUniformLocation(m_shader->getProgramID(), "uClipping.height");

		glUniform1i(uClippingClip, m_enableClipping);
		if(m_enableClipping)
		{
			glUniform1f(uClippingX, m_clip.x);
			glUniform1f(uClippingY, m_clip.y);
			glUniform1f(uClippingWidth, m_clip.width);
			glUniform1f(uClippingHeight, m_clip.height);
		}
	}
}

void Material::bindTexture(const Texture* texture)
{
	m_texture = texture;
	if(texture)
		glBindTexture(GL_TEXTURE_2D, texture->getID());
}

void Material::unbindTexture()
{
	m_texture = NULL;
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Material::disableShader()
{
	glUseProgram(0);
	m_isUsingShader = false;
}

const Shader* Material::getShader() const
{
	return m_shader;
}

void Material::deleteVbos()
{
	if(glIsBuffer(m_vboID))
		glDeleteBuffers(1, &m_vboID);
}

void Material::setOpacity(float opac)
{
	m_opacity = opac;
}

void Material::enableClipping(const Clipping& clip)
{
	m_clip = clip;
	m_enableClipping = true;
}

void Material::disableClipping()
{
	m_enableClipping = false;
}
