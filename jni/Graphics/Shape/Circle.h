#ifndef DEF_CIRCLE_INCLUDE
#define DEF_CIRCLE_INCLUDE

#include <cmath>
#include "Shape/TriangleShape.h"
#include "Materials/Material.h"

class Circle : public TriangleShape
{
	public:
		Circle(Material* material, float radius=1, int nbEdge=16); //size must be superior than 3. By default, radius is set to 1.0f. Set scale for setting radius.

		void setNbEdge(int nbEdge);
		int getNbEdge() const;
		glm::vec3 getCenter() const;
	private:
		static glm::vec3* initVertex(float radius, int nbEdge);
		float m_radius;
		int m_nbEdge;
		glm::vec3* buffer;
};
#endif
