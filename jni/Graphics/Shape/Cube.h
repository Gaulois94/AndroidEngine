#ifndef DEF_CUBE_INCLUDE
#define DEF_CUBE_INCLUDE

#include "Shape/TriangleShape.h"

/** \brief a Cube object*/
class Cube : public TriangleShape
{
	public:
		/** \brief The Cube constructor
		 * \param material the cube material
		 * \param width its width
		 * \param height its height
		 * \param depth its depth*/
		Cube(Material* material, float width, float height, float depth);
	protected:
		glm::vec3* initVertex(float width, float height, float depth);
		glm::vec3* buffer;
}

#endif
