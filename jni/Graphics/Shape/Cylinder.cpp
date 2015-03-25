#include "Cylinder.h"

Cylinder::Cylinder(Material* material, float radius, float height, int nbMeridian) : GroupDrawable(material)
{
	Circle* circle1 = new Circle(material, radius, nbMeridian);
	Circle* circle2 = new Circle(material, radius, nbMeridian);
	circle1->move(glm::vec3(0.0f, 0.0f, -height/2));
	circle2->move(glm::vec3(0.0f, 0.0f, height/2));
	m_drawables.add("circle1", circle1);
	m_drawables.add("circle2", circle2);
	m_drawables.add("lateral", new LateralCylinder(material, radius, height, nbMeridian));
}
