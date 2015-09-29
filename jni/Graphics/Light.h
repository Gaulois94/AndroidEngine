#ifndef DEF_LIGHT_INCLUDE
#define DEF_LIGHT_INCLUDE

#define PI 3.14159 
#define GLM_FORCE_RADIANS

#include "Color.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/** \brief Define a Light by a color, an intensity, an orientation and a position.*/
class Light
{
	public:
		/** \brief Init the Light.
		 * \param color the light's color
		 * \param position the light's position
		 * \param intensity the light's intensity
		 * \param phi the phi angle
		 * \param theta the theta angle*/
		Light(const Color& color, const glm::vec3& position, float intensity=0.25f, float phi = PI/2, float theta = 0);
		~Light();

		float m_phi;
		float m_theta;
		glm::vec2 m_intensity;
		glm::vec3 m_position;

		/** \brief Set the light's position.
		 * \param color the light's color */
		void setColor(const Color& color);

		/** \brief return the light's color.
		 * \return the light's color */
		Color getColor() const;
	private:
		float* m_color;
};

#endif
