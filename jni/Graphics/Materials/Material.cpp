#include "Materials/Material.h"

Material::Material(const Shader *shader) : m_shader(shader), m_texture(NULL), m_vboID(0), m_isUsingShader(false)
{}

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
	GLint uMaskColor     = glGetUniformLocation(m_shader->getProgramID(), "uMaskColor");
	GLint uUseTexture    = glGetUniformLocation(m_shader->getProgramID(), "uUseTexture");
	GLint uTextureHandle = glGetUniformLocation(m_shader->getProgramID(), "uTexture");

	if(m_texture)
	{
		float maskColor[4];
		m_texture->getMaskColor().getFloatArray(maskColor);
		glUniform4fv(uMaskColor, 1, maskColor);
		glUniform1i(uUseTexture, true);
		glUniform1i(uTextureHandle, 0);
	}

	else
		glUniform1i(uUseTexture, false);
}

void Material::bindTexture(const Texture* texture)
{
	m_texture = texture;
	if(texture)
		glBindTexture(GL_TEXTURE_2D, texture->getID());
}

void Material::unbindTexture()
{
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
