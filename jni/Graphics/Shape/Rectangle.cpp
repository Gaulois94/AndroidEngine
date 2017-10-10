#include "Shape/Rectangle.h"

Rectangle::Rectangle(Updatable* parent, Material* material, const glm::vec2& size) : TriangleShape(parent, material, buffer=initVertex(size), NULL, 4, GL_TRIANGLE_STRIP), m_size(size)
{
	free(buffer);
	buffer=NULL;
	glm::vec3 normalCoord[] = 
	{
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1)
	};
	setNormalCoord(normalCoord);
	setDefaultPos(glm::vec3(0.0, 0.0, 0.0));
	setDefaultSize(glm::vec3(m_size, 0.0));
}

glm::vec3* Rectangle::initVertex(const glm::vec2& size)
{
	glm::vec3* vertexCoord = (glm::vec3*)malloc(4*sizeof(glm::vec3));
	vertexCoord[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	vertexCoord[1] = glm::vec3(size.x, 0.0f, 0.0f);
	vertexCoord[2] = glm::vec3(0.0f, size.y, 0.0f);
	vertexCoord[3] = glm::vec3(size.x, size.y, 0.0f);

	return vertexCoord;
}
