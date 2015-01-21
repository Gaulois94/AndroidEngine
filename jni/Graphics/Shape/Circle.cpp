#include "Circle.h"

Circle::Circle(const Color& color, int nbEdge) : TriangleShape::TriangleShape(buffer=initVertex(nbEdge), 3*nbEdge, &color, true)
{
	free(buffer);
	buffer=NULL;
}

void Circle::setNbEdge(int nbEdge)
{
	m_nbEdge = nbEdge;
	glm::vec3* vertexCoords = initVertex(nbEdge);
	Color color = getUniColor();
	setDatas(vertexCoords, &color, 3*m_nbEdge, true);
	free(vertexCoords);
}

int Circle::getNbEdge() const
{
	return m_nbEdge;
}

glm::vec3* Circle::initVertex(int nbEdge)
{
	glm::vec3* vertexCoord = (glm::vec3*)malloc(nbEdge*3*sizeof(glm::vec3));

	for(int i=0; i < nbEdge; i++)
	{
		float pos[] = {
			0.0f, 0.0f, 0.0f,
			(float)cos(i*2*PI/nbEdge), (float)sin(i*2*PI/nbEdge), 0.0f,
			(float)cos((i+1)*2*PI/nbEdge), (float)sin((i+1)*2*PI/nbEdge), 0.0f};

		for(int j=0; j < 9; j++)
			vertexCoord[3*i+j/3][j%3] = pos[j];
	}

	return vertexCoord;
}
