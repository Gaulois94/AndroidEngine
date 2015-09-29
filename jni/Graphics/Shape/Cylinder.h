#ifndef DEF_CYLINDER_INCLUDE
#define DEF_CYLINDER_INCLUDE

#include "Shape/Circle.h"
#include "Shape/LateralCylinder.h"
#include "GroupDrawable.h"
#include "Materials/Material.h"

/** \brief The Cylinder class. It's only 2 circle plus the lateral face of the cylinder (LateralCylinder*/
class Cylinder : public GroupDrawable
{
	public:
		/** \brief the Cylinder constructor. It use the drawable LateralCylinder plus 2 circles
		 * \param material the Cylinder material
		 * \param radius the Cylinder radius
		 * \param height its height
		 * \param nbMeridian its number of meridian. must be superior then 3*/
		Cylinder(Material* material, float radius=1.0f, float height=2.0f, int nbMeridian=16);
	private:
};

#endif
