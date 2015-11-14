#include "Materials/UniColorMaterial.h"

UniColorMaterial::UniColorMaterial(const Color& color) : Material(Shader::shaders.get("color")), m_color(NULL)
{
	setColor(color);
}

UniColorMaterial::UniColorMaterial(const float* color) : Material(Shader::shaders.get("color")), m_color(NULL)
{
	setColor(color);
}

UniColorMaterial::~UniColorMaterial()
{
	if(m_color)
		free(m_color);
}

void UniColorMaterial::init(Render& render, const glm::mat4& mvp)
{
	Material::init(render, mvp);
	GLint vColor    = glGetAttribLocation(m_shader->getProgramID(), "vColor");
	glVertexAttrib4fv(vColor, m_color);
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
