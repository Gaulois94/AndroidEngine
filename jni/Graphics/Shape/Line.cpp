#include "Shape/Line.h"

Line::Line(Updatable* parent, Material* mtl, const std::vector<glm::vec3>& points) : TriangleShape(parent, mtl, &points[0], NULL, points.size(), GL_LINES)
{
}
