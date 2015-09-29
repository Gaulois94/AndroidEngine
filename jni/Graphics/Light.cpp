#include "Light.h"

Light::Light(const Color& color, const glm::vec3& position, float i, float p, float t) : phi(p), theta(t), position(pos), intensity(i)
{
	setColor(color);
}

Light::~Light()
{
	if(m_color)
		free(m_color);
}

void setColor(const Color& color)
{
	if(m_color)
		free(m_color);
	m_color = (float*) malloc(4*sizeof(float));
	color.getFloatArray(m_color);
}

Color Light::getColor() const
{
	return Color(m_color);
}
