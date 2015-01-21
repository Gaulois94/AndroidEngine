#ifndef DEF_CIRCLE_INCLUDE
#define DEF_CIRCLE_INCLUDE

#include <cmath>
#include "Shape/TriangleShape.h"

class Circle : public TriangleShape
{
	public:
		Circle(const Color& color, int nbEdge=16); //size must be superior than 3. By default, radius is set to 1.0f. Set scale for setting radius.

		void setNbEdge(int nbEdge);
		int getNbEdge() const;
	private:
		static glm::vec3* initVertex(int nbEdge);
		int m_nbEdge;
		glm::vec3* buffer;
};
#endif
