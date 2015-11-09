#include "Materials/ExplosionMaterial.h"

ExplosionMaterial::ExplosionMaterial(const Color& baseColor) : EffectMaterial(Shader::shaders.get("effect/explosion"))
{
	m_color[0] = baseColor.r;
	m_color[1] = baseColor.g;
	m_color[2] = baseColor.b;
	m_color[3] = baseColor.a;
}

void ExplosionMaterial::init(Render& render, const glm::mat4& mvp)
{
	EffectMaterial::init(render, mvp);
	GLint uBaseColor = glGetUniformLocation(m_shader->getProgramID(), "uBaseColor");

	glUniform4fv(uBaseColor, 1, m_color);
}
