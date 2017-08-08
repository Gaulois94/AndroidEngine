#include "Materials/TextureMaterial.h"

TextureMaterial::TextureMaterial() : Material(Shader::shaders.get("texture"))
{
	getAttributs();
}

void TextureMaterial::init(Render& render, const glm::mat4& mvp, const glm::mat4& modelMatrix)
{
	Material::init(render, mvp, modelMatrix);
	if(m_uType != -1)
		glUniform1i(m_uType, (int)m_colorMode);
}

void TextureMaterial::getAttributs()
{
	m_uType = glGetUniformLocation(m_shader->getProgramID(), "uColorMode");
}
