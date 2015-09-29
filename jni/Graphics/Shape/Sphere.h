#ifndef DEF_SPHERE_INCLUDE
#define DEF_SPHERE_INCLUDE

#include "TriangleShape.h"
#include <cmath>

/** \brief a Sphere class*/
class Sphere : public TriangleShape
{
	public:
		/** \brief Sphere constructor.
		 * \param material its material
		 * \param radius its radius
		 * \param nbLongitude its number of longitude. Must be superior than 3
		 * \param nbLatitude its number of latitude. Must be superior than 3*/
		Sphere(Material* material, float radius=1.0f, unsigned int nbLongitude=16, unsigned int nbLatitude=32);
	private:
		static glm::vec3*    initVertex(float radius, unsigned int nbLongitude, unsigned int nbLatitude);
		static unsigned int* initOrder(unsigned int nbLongitude, unsigned int nbLatitude);
		unsigned int m_nbLongitude;
		unsigned int m_nbLatitude;
		glm::vec3* buffer;
};

#endif
