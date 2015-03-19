#include "Shape/Rectangle.h"

Rectangle::Rectangle(Material* material, const glm::vec2& size) : TriangleShape(material, buffer=initVertex(size), NULL, 4), m_size(size)
{
	free(buffer);
	buffer=NULL;
	unsigned int drawOrder[] = {0, 1, 2, 0, 2, 3};
	setDrawOrder(drawOrder, 6);
}

glm::vec3* Rectangle::initVertex(const glm::vec2& size)
{
	glm::vec3* vertexCoord = (glm::vec3*)malloc(4*sizeof(glm::vec3));
	vertexCoord[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	vertexCoord[1] = glm::vec3(size.x, 0.0f, 0.0f);
	vertexCoord[2] = glm::vec3(size.x, size.y, 0.0f);
	vertexCoord[3] = glm::vec3(0.0f, size.y, 0.0f);

	return vertexCoord;
}
