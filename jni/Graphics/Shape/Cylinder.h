#ifndef DEF_CYLINDER_INCLUDE
#define DEF_CYLINDER_INCLUDE

#include "Shape/Circle.h"
#include "Shape/LateralCylinder.h"
#include "GroupDrawable.h"
#include "Materials/Material.h"

class Cylinder : public GroupDrawable
{
	public:
		Cylinder(Material* material, float radius=1.0f, float height=2.0f, int nbMeridian=16);
	private:
};

#endif
