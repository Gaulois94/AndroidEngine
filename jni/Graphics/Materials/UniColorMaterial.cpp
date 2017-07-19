#include "Materials/UniColorMaterial.h"

UniColorMaterial::UniColorMaterial(const Color& color) : Material(Shader::shaders.get("color")), m_color(NULL)
{
	setColor(color);
	if(!getShader())
		return;
	getAttributs();
}

UniColorMaterial::UniColorMaterial(const float* color) : Material(Shader::shaders.get("color")), m_color(NULL)
{
	setColor(color);
	getAttributs();
}

UniColorMaterial::~UniColorMaterial()
{
	if(m_color)
		free(m_color);
}

void UniColorMaterial::init(Render& render, const glm::mat4& mvp, const glm::mat4& modelMatrix)
{
	Material::init(render, mvp, modelMatrix);
	if(m_uColor != -1)
		glUniform4fv(m_uColor, 1, m_color);
	if(m_uUseUniColor != -1)
		glUniform1i(m_uUseUniColor, true);
}

void UniColorMaterial::disableShader()
{
}

void UniColorMaterial::setColor(const Color& color)
{
	if(m_color)
		free(m_color);
	m_color = (float*)malloc(4*sizeof(float));
	color.getFloatArray(m_color);
}

void UniColorMaterial::setColor(const float* color)
{
	if(m_color)
		free(m_color);
	m_color = (float*)malloc(4*sizeof(float));
	memcpy(m_color, color, 4*sizeof(float));
}

Color UniColorMaterial::getColor() const
{
	return Color(m_color);
}

void UniColorMaterial::getAttributs()
{
	Material::getAttributs();
	m_uColor       = glGetUniformLocation(m_shader->getProgramID(), "uUniColor");
	m_uUseUniColor = glGetUniformLocation(m_shader->getProgramID(), "uUseUniColor");
}
