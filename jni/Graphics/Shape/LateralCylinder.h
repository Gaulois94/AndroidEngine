#ifndef DEF_LATERALCYLINDER_INCLUDE
#define DEF_LATERALCYLINDER_INCLUDE

#include "Shape/TriangleShape.h"
#include "Materials/Material.h"
#include <cmath>

class LateralCylinder : public TriangleShape
{
	public:
		LateralCylinder(Material* material, float radius=1.0f, float height=2.0f, int nbMeridian=16);
		int getNbMeridian();
	private:
		static glm::vec3* initVertex(float radius, float height, int nbMeridian);
		static glm::vec3* initNormal(int nbMeridian);
		int m_nbMeridian;
		glm::vec3* buffer;
};

#endif
