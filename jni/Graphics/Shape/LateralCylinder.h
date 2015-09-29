#ifndef DEF_LATERALCYLINDER_INCLUDE
#define DEF_LATERALCYLINDER_INCLUDE

#include "Shape/TriangleShape.h"
#include "Materials/Material.h"
#include <cmath>

/** \brief the lateral face of on cylinder. It use nbMeridian rectangles around the axis y*/
class LateralCylinder : public TriangleShape
{
	public:
		/** \brief the LateralCylinder constructor.
		 * \param material its material
		 * \param radius its radius
		 * \param height its height
		 * \param nbMeridian its number of meridians. Must be superior than 3*/
		LateralCylinder(Material* material, float radius=1.0f, float height=2.0f, int nbMeridian=16);

		/** \brief get the number of meridian of this LateralCylinder
		 * \return the number of meridians*/
		int getNbMeridian();
	private:
		static glm::vec3* initVertex(float radius, float height, int nbMeridian);
		static glm::vec3* initNormal(int nbMeridian);
		int m_nbMeridian;
		glm::vec3* buffer;
};

#endif
