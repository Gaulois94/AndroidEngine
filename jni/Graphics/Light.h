#ifndef DEF_LIGHT_INCLUDE
#define DEF_LIGHT_INCLUDE

#define PI 3.14159 
#define GLM_FORCE_RADIANS

#include "Color.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light
{
	public:
		Light(const Color& color, const glm::vec3& position, float intensity=0.25f, const glm::vec2& phi = glm::vec2(-PI/2, PI/2), const glm::vec2& theta = glm::vec2(0, 2*PI));
		~Light();

		glm::vec2 m_phi;
		glm::vec2 m_theta;
		glm::vec2 m_intensity;
		glm::vec3 m_position;

		void setColor(const Color& color);
		Color getColor() const;
	private:
		float* m_color;
};

#endif
