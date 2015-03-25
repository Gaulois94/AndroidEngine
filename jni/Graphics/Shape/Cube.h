#ifndef DEF_CUBE_INCLUDE
#define DEF_CUBE_INCLUDE

#include "Shape/TriangleShape.h"

class Cube : public TriangleShape
{
	public:
		Cube(Material* material, float width, float height, float depth);
	protected:
		glm::vec3* initVertex(float width, float height, float depth);
		glm::vec3* buffer;
}

#endif
