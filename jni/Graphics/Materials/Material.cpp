#include "Materials/Material.h"

float Material::maskColor[4];
Rectangle2f Material::globalClipping;
bool Material::globalEnableClipping=false;

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
	GLint uMaskColor          = glGetUniformLocation(m_shader->getProgramID(), "uMaskColor");
	GLint uUseTexture         = glGetUniformLocation(m_shader->getProgramID(), "uUseTexture");
	GLint uTextureHandle      = glGetUniformLocation(m_shader->getProgramID(), "uTexture");
	GLint uOpacityHandle      = glGetUniformLocation(m_shader->getProgramID(), "uOpacity");
	GLint uModelMatrix        = glGetUniformLocation(m_shader->getProgramID(), "uModelMatrix");

	GLint uLocalClippingClip  = glGetUniformLocation(m_shader->getProgramID(), "uLocalClipping.clip");
	GLint uGlobalClippingClip = glGetUniformLocation(m_shader->getProgramID(), "uGlobalClipping.clip");

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

	if(uLocalClippingClip != -1)
	{
		GLint uLocalClippingX      = glGetUniformLocation(m_shader->getProgramID(), "uLocalClipping.x");
		GLint uLocalClippingY      = glGetUniformLocation(m_shader->getProgramID(), "uLocalClipping.y");
		GLint uLocalClippingWidth  = glGetUniformLocation(m_shader->getProgramID(), "uLocalClipping.width");
		GLint uLocalClippingHeight = glGetUniformLocation(m_shader->getProgramID(), "uLocalClipping.height");

		glUniform1i(uLocalClippingClip, m_enableClipping);
        glUniform1f(uLocalClippingX, m_clip.x);
        glUniform1f(uLocalClippingY, m_clip.y);
        glUniform1f(uLocalClippingWidth, m_clip.width);
        glUniform1f(uLocalClippingHeight, m_clip.height);
    }

    if(uGlobalClippingClip != -1)
    {
		GLint uGlobalClippingX      = glGetUniformLocation(m_shader->getProgramID(), "uGlobalClipping.x");
		GLint uGlobalClippingY      = glGetUniformLocation(m_shader->getProgramID(), "uGlobalClipping.y");
		GLint uGlobalClippingWidth  = glGetUniformLocation(m_shader->getProgramID(), "uGlobalClipping.width");
		GLint uGlobalClippingHeight = glGetUniformLocation(m_shader->getProgramID(), "uGlobalClipping.height");

		glUniform1i(uGlobalClippingClip, Material::globalEnableClipping);
        glUniform1f(uGlobalClippingX, Material::globalClipping.x);
        glUniform1f(uGlobalClippingY, Material::globalClipping.y);
        glUniform1f(uGlobalClippingWidth, Material::globalClipping.width);
        glUniform1f(uGlobalClippingHeight, Material::globalClipping.height);
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

void Material::setClipping(const Rectangle2f& clip)
{
	m_clip = clip;
}

void Material::enableClipping(bool enable)
{
	m_enableClipping = enable;
}

void Material::setGlobalClipping(const Rectangle2f& clip)
{
	Material::globalClipping = clip;
}

void Material::enableGlobalClipping(bool enable)
{
	Material::globalEnableClipping = enable;
}

const Rectangle2f& Material::getGlobalClipping()
{
	return Material::globalClipping;
}

bool Material::getGlobalEnableClipping()
{
	return Material::globalEnableClipping;
}
