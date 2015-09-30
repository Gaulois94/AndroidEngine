#ifndef DEF_RECTANGLE_INCLUDE
#define DEF_RECTANGLE_INCLUDE

#include "Shape/TriangleShape.h"
#include "Texture.h"

/** \brief A 2D Rectangle class*/
class Rectangle : public TriangleShape
{
	public:
		/** \brief The Rectangle constructor
		 * \param parent its parent
		 * \param material its material
		 * \param size its size (x, y). By default it's (1.0, 1.0) (thus it will be a square). If you want to change this later, be free to scale this Drawable.*/
		Rectangle(Updatable* parent, Material* material, const glm::vec2& size = glm::vec2(1.0, 1.0));
	private:
		static glm::vec3* initVertex(const glm::vec2& size);
		glm::vec3* buffer;
		glm::vec2 m_size;
};
#endif
