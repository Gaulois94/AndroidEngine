#include "CheckBox.h"

CheckBox::CheckBox(Updatable* parent, Material* material, const glm::vec2& size) : Widget(parent, material), 
{
	Rectangle* m_rectangle = new Rectangle(NULL, material, size);
	TriangleShape* m_cross = new TriangleShape(NULL, material, NULL, NULL, 0, GL_LINE);
	glm::vec3 normalCoord[] = {
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1)
	}

	glm::vec3 vertexPos[] = {
		glm::vec3(0, 0, 0),
		glm::vec3(1, 1, 0)
		glm::vec3(0, 1, 0),
		glm::vec3(1, 0, 0)
	}

	m_cross->setDatas(vertexPos, normalCoord, 4);
	m_drawables.add("cross", m_cross);
	m_drawables.add("rectangle", m_rectangle);
}

void CheckBox::onUpdate(Render &render)
{
	Active::update();
	Widget::onUpdate(render);
}

void CheckBox::onDraw(Render &render, const glm::mat4& transformation)
{
	render.draw(m_rectangle, getMatrix());
	render.draw(m_cross, getMatrix());
}

void CheckBox::setCrossMaterial(Material* material)
{
	m_cross.setMaterial(material);
}

void setRectangleMaterial(Material* material)
{
	m_rectangle.setMaterial(material);
}
