#include "Circle.h"

Circle::Circle(Material* material, float radius, int nbEdge) : TriangleShape::TriangleShape(material, buffer=initVertex(radius, nbEdge), NULL, 3*nbEdge), m_radius(radius)
{
	free(buffer);
	buffer=NULL;
}

void Circle::setNbEdge(int nbEdge)
{
	m_nbEdge = nbEdge;
	glm::vec3* vertexCoords = initVertex(m_radius, nbEdge);
	setVertexCoord(vertexCoords);
	free(vertexCoords);
}

int Circle::getNbEdge() const
{
	return m_nbEdge;
}

glm::vec3 Circle::getCenter() const
{
	return getPosition() + glm::vec3(1.0f, -1.0f, 0.0f);
}

glm::vec3* Circle::initVertex(float radius, int nbEdge)
{
	glm::vec3* vertexCoord = (glm::vec3*)malloc(nbEdge*3*sizeof(glm::vec3));

	for(int i=0; i < nbEdge; i++)
	{
		float pos[] = {
			radius, 0.0f, 0.0f,
			radius + radius*(float)cos(i*2*PI/nbEdge), radius*(float)sin(i*2*PI/nbEdge), 0.0f,
			radius + radius*(float)cos((i+1)*2*PI/nbEdge), radius*(float)sin((i+1)*2*PI/nbEdge), 0.0f};

		for(int j=0; j < 9; j++)
			vertexCoord[3*i+j/3][j%3] = pos[j];
	}

	return vertexCoord;
}
