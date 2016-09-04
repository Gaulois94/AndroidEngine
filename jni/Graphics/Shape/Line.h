#ifndef  LINE_INC
#define  LINE_INC

#include "Graphics/Drawable.h"
#include "Graphics/Shape/TriangleShape.h"

class Line : public TriangleShape
{
	public:
		Line(Updatable* parent, Material* mtl, const std::vector<glm::vec3>& points);
};

#endif
