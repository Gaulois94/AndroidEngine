#include "Shape/Cube.h"

Cube::Cube(Updatable* parent, Material* material, float width, float height, float depth) : TriangleShape(parent, buffer=initVertex(width, height, depth), NULL, 36)
{
	free(buffer);

	//generate the normalCoord of this cube
	glm::vec3 normalCoord[36];
	uint32_t i=0
	//top side
	for(; i < 6; i++)
		normalCoord[i] = glm::vec3(0, 1, 0);

	//bottom side
	for(; i < 2*6; i++)
		normalCoord[i] = glm::vec3(0, -1, 0);

	//right side
	for(; i < 3*6; i++)
		normalCoord[i] = glm::vec3(1, 0, 0);
	
	//left side
	for(; i < 4*6; i++)
		normalCoord[i] = glm::vec3(-1, 0, 0);
	
	//back side
	for(; i < 5*6; i++)
		normalCoord[i] = glm::vec3(0, 0, -1);
	
	//front side
	for(; i < 6*6; i++)
		normalCoord[i] = glm::vec3(0, 0, 1);

	setNormalCoord(normalCoord);
}

glm::vec3* Cube::initVertex(float width, float height, float depth)
{
	float pos[] = {0,  height, depth,
				   width,   height, depth,
				   width,   height, 0,
				   //top side
				   0,  height, depth,
				   width,   height, 0,
				   0,  height, 0,

				   0, 0, depth,
				   width,  0, depth, 
				   width,  0, 0,
				   //bottom side
				   0, 0, depth,
				   width,  0, 0,
				   0, 0, 0,



				   width, 0, depth,
				   width, 0, 0,
				   width, height, 0,
				   //right side
				   width, 0, depth,
				   width, height, 0,
				   width, height, depth,

				   0, 0, depth,
				   0, 0, 0,
				   0, height, 0,
				   //left side
				   0, 0, depth,
				   0, height, 0,
				   0, height, depth,



				   0, 0,  depth,
				   width, 0,   depth,
				   width, height,    depth,
				   //back side
				   0, 0,  depth,
				   0, height,   depth,
				   width, height,    depth,

				   0, 0, 0,
				   width, 0,  0,
				   width, height,   0,
				   //front side
				   0, 0, 0,
				   0, height,  0,
				   width, height,   0
				  };

	glm::vec3* vertexCoords = (glm::vec3*)malloc(sizeof(glm::vec3*)*36);
	for(int i=0; i < 36; i++)
		for(int j=0; j < 3; j++)
			vertexCoords[i][j] = pos[i*3+j];

	return vertexCoords;
}
