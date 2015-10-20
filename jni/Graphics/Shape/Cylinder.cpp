#include "Cylinder.h"

Cylinder::Cylinder(Updatable* parent, Material* material, float radius, float height, int nbMeridian) : GroupDrawable(parent, material, Rectangle3f(0, 0, 0, 0, 0, 0))
{
	//Create and add to its child the different 
	Circle* circle1 = new Circle(NULL, material, radius, nbMeridian);
	Circle* circle2 = new Circle(NULL, material, radius, nbMeridian);
	LateralCylinder* lateralCylinder = new LateralCylinder(NULL, material, radius, height, nbMeridian);
	circle1->move(glm::vec3(0.0f, 0.0f, -height/2));
	circle2->move(glm::vec3(0.0f, 0.0f, height/2));

	m_drawables.push_back(circle1);
	m_drawables.push_back(circle2);
	m_drawables.push_back(lateralCylinder);

	//Define the default configuration of a cylinder
	glm::vec3 cDefaultSize  = circle1->getDefaultSize();
	glm::vec3 cDefaultPos   = circle1->getPosition();
	Rectangle3f defaultConf = Rectangle3f(cDefaultPos.x, cDefaultPos.y, cDefaultPos.z, cDefaultSize.x, cDefaultSize.y, height);
	setDefaultConf(defaultConf);

	deleteAuto(true);
}
