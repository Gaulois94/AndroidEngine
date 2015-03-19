#ifndef DEF_SPHERE_INCLUDE
#define DEF_SPHERE_INCLUDE

#include "TriangleShape.h"
#include <cmath>

class Sphere : public TriangleShape
{
	public:
		Sphere(Material* material, unsigned int nbLongitude, unsigned int nbLatitude);
	private:
		static glm::vec3*    initVertex(unsigned int nbLongitude, unsigned int nbLatitude);
		static unsigned int* initOrder(unsigned int nbLongitude, unsigned int nbLatitude);
		unsigned int m_nbLongitude;
		unsigned int m_nbLatitude;
		glm::vec3* buffer;
};

#endif
