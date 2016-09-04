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

void Material::init(Render& render, const glm::mat4& mvp)
{
	if(!m_shader)
		return;
	GLint uMaskColor     = glGetUniformLocation(m_shader->getProgramID(), "uMaskColor");
	GLint uUseTexture    = glGetUniformLocation(m_shader->getProgramID(), "uUseTexture");
	GLint uTextureHandle = glGetUniformLocation(m_shader->getProgramID(), "uTexture");

	GLint uOpacityHandle = glGetUniformLocation(m_shader->getProgramID(), "uOpacity");

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
