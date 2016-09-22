#include "Materials/LineMaterial.h"

LineMaterial::LineMaterial(const Color& c, float t) : Material(Shader::shaders.get("line")), m_thickness(t)
{
	c.getFloatArray(m_color);
}

void LineMaterial::setColor(const Color& c)
{
	c.getFloatArray(m_color);
}

void LineMaterial::setThickness(float t)
{
	m_thickness = t;
}

void LineMaterial::init(Render& render, const glm::mat4& mvp, const glm::mat4& modelMatrix)
{
	Material::init(render, mvp, modelMatrix);
	glLineWidth(m_thickness);
	GLint uColor = glGetUniformLocation(m_shader->getProgramID(), "uColor");
	glUniform3fv(uColor, 1, m_color);
}
