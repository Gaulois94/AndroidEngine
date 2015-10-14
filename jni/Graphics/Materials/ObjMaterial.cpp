#include "Materials/ObjMaterial.h"

ObjMaterial::ObjMaterial(const Color& diffuseColor, const Color& specularColor, const Texture* texture, bool useT, bool hlOn, bool aOn, bool cOn, float spHl, float alpha) : Material(Shader::shaders.get("obj")),
	transparent(alpha), specularHighlight(spHl), colorOn(cOn), ambientOn(aOn), highlightOn(hlOn), m_diffuseColor(NULL), m_specularColor(NULL)
{
	setDiffuseColor(diffuseColor);
	setSpecularColor(specularColor);
	bindTexture(texture);
}

void ObjMaterial::init(Render& render, const glm::mat4& mvp)
{
	Material::init(render, mvp);
	GLint ambientColorHandle      = glGetUniformLocation(m_shader->getProgramID(), "uAmbientColor");
	GLint diffuseColorHandle      = glGetUniformLocation(m_shader->getProgramID(), "uDiffuseColor");
	GLint specularColorHandle     = glGetUniformLocation(m_shader->getProgramID(), "uSpecularColor");
	GLint transparentHandle       = glGetUniformLocation(m_shader->getProgramID(), "uTransparent");
	GLint specularHighlightHandle = glGetUniformLocation(m_shader->getProgramID(), "uSpecularHighlight");
	GLint cameraMvpHandle         = glGetUniformLocation(m_shader->getProgramID(), "uCameraMVP");
	GLint inverseCameraMvpHandle  = glGetUniformLocation(m_shader->getProgramID(), "uInverseCameraMVP");
	GLint uInverseMvp             = glGetUniformLocation(m_shader->getProgramID(), "uInverseMVP");
	GLint uTransposeMvp           = glGetUniformLocation(m_shader->getProgramID(), "uTransposeInverseMVP");
	GLint uTransformation         = glGetUniformLocation(m_shader->getProgramID(), "uTransformationMVP");

	Color aC = render.getAmbientColor();
	glm::mat4 inverseMvp    = glm::inverse(mvp);
	glm::mat4 inverseCamera = glm::inverse(render.getCamera().getMatrix());

	float ambientColor[3]   = {0.25, 0.25, 0.25};
	glUniform3fv(ambientColorHandle, 1, ambientColor);
	glUniform3fv(diffuseColorHandle, 1, m_diffuseColor);
	glUniform3fv(specularColorHandle, 1, m_specularColor);
	glUniform1f(transparentHandle, transparent);
	glUniform1f(specularHighlightHandle, specularHighlight);
	glUniformMatrix4fv(cameraMvpHandle, 1, false, glm::value_ptr(render.getCamera().getMatrix()));
	glUniformMatrix4fv(inverseCameraMvpHandle, 1, false, glm::value_ptr(inverseCamera));

	glUniformMatrix4fv(uInverseMvp, 1, false, glm::value_ptr(inverseMvp));
	glUniformMatrix4fv(uTransposeMvp, 1, false, glm::value_ptr(glm::transpose(inverseMvp)));
	glUniformMatrix4fv(uTransformation, 1, false, glm::value_ptr(inverseCamera * mvp));
}

void ObjMaterial::setDiffuseColor(const Color& diffuseColor)
{
	if(m_diffuseColor)
		free(m_diffuseColor);
	m_diffuseColor = (float*) malloc(4*sizeof(float));
	diffuseColor.getFloatArray(m_diffuseColor);
}

void ObjMaterial::setSpecularColor(const Color& specularColor)
{
	if(m_specularColor)
		free(m_specularColor);
	m_specularColor = (float*) malloc(4*sizeof(float));
	specularColor.getFloatArray(m_specularColor);
}

Color ObjMaterial::getDiffuseColor() const
{
	return Color(m_diffuseColor);
}

Color ObjMaterial::getSpecularColor() const
{
	return Color(m_specularColor);
}
