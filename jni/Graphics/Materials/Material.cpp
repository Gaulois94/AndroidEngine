#include "Materials/Material.h"

float Material::maskColor[4];
Rectangle2f Material::globalClipping;
bool Material::globalEnableClipping=false;

Material::Material(const Shader *shader) : m_shader(shader), m_texture(NULL), m_vboID(0), m_isUsingShader(false)
{
	if(!m_shader)
		LOG_ERROR("ERROR LOADING SHADER");
	getAttributs();
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

	if(m_texture)
	{
		if(m_uMaskColor != -1)
		{
			m_texture->getMaskColor().getFloatArray(maskColor);
			glUniform4fv(m_uMaskColor, 1, maskColor);
		}
		if(m_uUseTexture != -1)
			glUniform1i(m_uUseTexture, true);
		if(m_uTextureHandle != -1)
			glUniform1i(m_uTextureHandle, 0);
	}

	else
	{
		if(m_uMaskColor != -1)
			glUniform4fv(m_uMaskColor, 1, maskColor);
		if(m_uUseTexture != -1)
			glUniform1i(m_uUseTexture, false);
		if(m_uTextureHandle != -1)
			glUniform1i(m_uTextureHandle, 0);
	}

	if(m_uOpacityHandle != -1)
		glUniform1f(m_uOpacityHandle, m_opacity);

	if(m_uModelMatrix != -1)
		glUniformMatrix4fv(m_uModelMatrix, 1, false, glm::value_ptr(modelMatrix));

	if(m_uLocalClippingClip != -1)
	{
		glUniform1i(m_uLocalClippingClip, m_enableClipping);
        glUniform1f(m_uLocalClippingX, m_clip.x);
        glUniform1f(m_uLocalClippingY, m_clip.y);
        glUniform1f(m_uLocalClippingWidth, m_clip.width);
        glUniform1f(m_uLocalClippingHeight, m_clip.height);
    }

    if(m_uGlobalClippingClip != -1)
    {

		glUniform1i(m_uGlobalClippingClip, Material::globalEnableClipping);
        glUniform1f(m_uGlobalClippingX, Material::globalClipping.x);
        glUniform1f(m_uGlobalClippingY, Material::globalClipping.y);
        glUniform1f(m_uGlobalClippingWidth, Material::globalClipping.width);
        glUniform1f(m_uGlobalClippingHeight, Material::globalClipping.height);
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

void Material::getAttributs()
{
	m_uMaskColor            = glGetUniformLocation(m_shader->getProgramID(), "uMaskColor");
	m_uUseTexture           = glGetUniformLocation(m_shader->getProgramID(), "uUseTexture");
	m_uTextureHandle        = glGetUniformLocation(m_shader->getProgramID(), "uTexture");
	m_uOpacityHandle        = glGetUniformLocation(m_shader->getProgramID(), "uOpacity");
	m_uModelMatrix          = glGetUniformLocation(m_shader->getProgramID(), "uModelMatrix");

	m_uLocalClippingClip    = glGetUniformLocation(m_shader->getProgramID(), "uLocalClipping.clip");
	m_uGlobalClippingClip   = glGetUniformLocation(m_shader->getProgramID(), "uGlobalClipping.clip");

	m_uLocalClippingX       = glGetUniformLocation(m_shader->getProgramID(), "uLocalClipping.x");
	m_uLocalClippingY       = glGetUniformLocation(m_shader->getProgramID(), "uLocalClipping.y");
	m_uLocalClippingWidth   = glGetUniformLocation(m_shader->getProgramID(), "uLocalClipping.width");
	m_uLocalClippingHeight  = glGetUniformLocation(m_shader->getProgramID(), "uLocalClipping.height");

	m_uGlobalClippingX      = glGetUniformLocation(m_shader->getProgramID(), "uGlobalClipping.x");
	m_uGlobalClippingY      = glGetUniformLocation(m_shader->getProgramID(), "uGlobalClipping.y");
	m_uGlobalClippingWidth  = glGetUniformLocation(m_shader->getProgramID(), "uGlobalClipping.width");
	m_uGlobalClippingHeight = glGetUniformLocation(m_shader->getProgramID(), "uGlobalClipping.height");
}
