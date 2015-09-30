#include "Shape/Cube.h"

Cube::Cube(Updatable* parent, Material* material, float width, float height, float depth) : TriangleShape(parent, buffer=initVertex(width, height, depth), NULL, 36)
{
	free(buffer);
}

glm::vec3* Cube::initVertex(float width, float height, float depth)
{
	float pos[] = {-width/2,  height/2, depth/2,
				   width/2,   height/2, depth/2,
				   width/2,   height/2, -depth/2,

				   -width/2,  height/2, depth/2,
				   width/2,   height/2, -depth/2,
				   -width/2,  height/2, -depth/2,

				   -width/2, -height/2, depth/2,
				   width/2,  -height/2, depth/2,
				   width/2,  -height/2, -depth/2,

				   -width/2, -height/2, depth/2,
				   width/2,  -height/2, -depth/2,
				   -width/2, -height/2, -depth/2,



				   width/2, -height/2, depth/2,
				   width/2, -height/2, -depth/2,
				   width/2, height/2, -depth/2,

				   width/2, -height/2, depth/2,
				   width/2, height/2, -depth/2,
				   width/2, height/2, depth/2,

				   -width/2, -height/2, depth/2,
				   -width/2, -height/2, -depth/2,
				   -width/2, height/2, -depth/2,

				   -width/2, -height/2, depth/2,
				   -width/2, height/2, -depth/2,
				   -width/2, height/2, depth/2,



				   -width/2, -height/2,  depth/2,
				   width/2, -height/2,   depth/2,
				   width/2, height/2,    depth/2,

				   -width/2, -height/2,  depth/2,
				   -width/2, height/2,   depth/2,
				   width/2, height/2,    depth/2,

				   -width/2, -height/2, -depth/2,
				   width/2, -height/2,  -depth/2,
				   width/2, height/2,   -depth/2,

				   -width/2, -height/2, -depth/2,
				   -width/2, height/2,  -depth/2,
				   width/2, height/2,   -depth/2
				  };

	glm::vec3* vertexCoords = (glm::vec3*)malloc(sizeof(glm::vec3*)*36);
	for(int i=0; i < 36; i++)
		for(int j=0; j < 3; j++)
			vertexCoords[i][j] = pos[i*3+j];

	return vertexCoords;
}
