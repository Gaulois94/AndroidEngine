#ifndef DEF_SPHERE_INCLUDE
#define DEF_SPHERE_INCLUDE

#include "TriangleShape.h"
#include <cmath>

class Sphere : public TriangleShape
{
	public:
		Sphere(Material* material, float radius=1.0f, unsigned int nbLongitude=16, unsigned int nbLatitude=32);
	private:
		static glm::vec3*    initVertex(float radius, unsigned int nbLongitude, unsigned int nbLatitude);
		static unsigned int* initOrder(unsigned int nbLongitude, unsigned int nbLatitude);
		unsigned int m_nbLongitude;
		unsigned int m_nbLatitude;
		glm::vec3* buffer;
};

#endif
