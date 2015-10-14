#include "Circle.h"

Circle::Circle(Updatable* parent, Material* material, float radius, uint32_t nbEdge) : TriangleShape(parent, material, buffer=initVertex(radius, nbEdge), NULL, 3*nbEdge), m_radius(radius)
{
	free(buffer);
	buffer=NULL;

	//Set the normalCoord of this Circle. All the vertices has the same normal coordinates
	glm::vec3* normalCoord = (glm::vec3*)malloc(nbEdge*3*sizeof(glm::vec3));
	for(uint32_t i=0; i < nbEdge*3; i++)
		normalCoord[i] = glm::vec3(0, 0, 1);
	setNormalCoord(normalCoord);
	free(normalCoord);
}

void Circle::setNbEdge(uint32_t nbEdge, float radius)
{
	m_nbEdge = nbEdge;
	glm::vec3* vertexCoords = initVertex(radius, nbEdge);
	setVertexCoord(vertexCoords);
	free(vertexCoords);
}

int Circle::getNbEdge() const
{
	return m_nbEdge;
}

glm::vec3 Circle::getCenter() const
{
	return getPosition();
}

glm::vec3* Circle::initVertex(float radius, int nbEdge)
{
	glm::vec3* vertexCoord = (glm::vec3*)malloc(nbEdge*3*sizeof(glm::vec3));

	for(int i=0; i < nbEdge; i++)
	{
		float pos[] = {
			0.0f, 0.0f, 0.0f,
			radius*(float)cos(i*2*PI/nbEdge), radius*(float)sin(i*2*PI/nbEdge), 0.0f,
			radius*(float)cos((i+1)*2*PI/nbEdge), radius*(float)sin((i+1)*2*PI/nbEdge), 0.0f};

		for(int j=0; j < 9; j++)
			vertexCoord[3*i+j/3][j%3] = pos[j];
	}

	return vertexCoord;
}
