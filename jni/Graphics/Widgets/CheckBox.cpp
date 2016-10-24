#include "CheckBox.h"

CheckBox::CheckBox(Updatable* parent, Material* material, const glm::vec2& size) : GroupDrawable(parent, material, Rectangle3f(0.0, 0.0, 0.0, size[0], size[1], 0.0)), m_rectangle(NULL), m_cross(NULL)
{
	m_activeOnce = false;
	m_alwaysUpdateSelection = false;
	m_alwaysUpdateActivation = false;
	m_rectangle = new Rectangle(NULL, material, size);
	glm::vec3 normalCoords[] = {
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1)
	};

	glm::vec3 vertexCoords[] = {
		glm::vec3(0, 0, 0),
		glm::vec3(size.x, size.y, 0),
		glm::vec3(0, size.y, 0),
		glm::vec3(size.x, 0, 0)
	};

	m_cross = new TriangleShape(NULL, material, vertexCoords, normalCoords, 4, GL_LINES);
	m_cross->setCanDraw(false);
	m_activeOnce = false;
	m_drawables.push_back(m_rectangle);
	m_drawables.push_back(m_cross);
	m_updateFocus = true;
}

CheckBox::~CheckBox()
{
	delete m_cross;
	delete m_rectangle;
}

void CheckBox::onFocus(const TouchEvent& te, Render& render)
{
	if(m_isActive)
		disactiveIt();
	else
		activeIt();
}

void CheckBox::onUpdate(Render &render)
{
	Active::update();
	GroupDrawable::onUpdate(render);
}

void CheckBox::setCrossMaterial(Material* material)
{
	m_cross->setMaterial(material);
}

void CheckBox::setRectangleMaterial(Material* material)
{
	m_rectangle->setMaterial(material);
}

void CheckBox::activeIt()
{
	Active::activeIt();
	m_cross->setCanDraw(true);
}

void CheckBox::disactiveIt()
{
	Active::disactiveIt();
	m_cross->setCanDraw(false);
}
