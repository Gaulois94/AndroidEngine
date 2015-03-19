#ifndef DEF_RECTANGLE_INCLUDE
#define DEF_RECTANGLE_INCLUDE

#include "Shape/TriangleShape.h"
#include "Texture.h"

class Rectangle : public TriangleShape
{
	public:
		Rectangle(Material* material, const glm::vec2& size = glm::vec2(1.0, 1.0));
	private:
		static glm::vec3* initVertex(const glm::vec2& size);
		glm::vec3* buffer;
		glm::vec2 m_size;
};
#endif
