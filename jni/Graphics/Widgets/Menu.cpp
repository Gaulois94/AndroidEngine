#include "Widgets/Menu.h"

Menu::Menu(Updatable* parent, Drawable* title, const glm::vec3& defPos, Drawable* background) : GroupDrawable(parent, NULL, Rectangle3f(defPos, glm::vec3(0, 0, 0))),
	m_title(title), m_background(background), m_fireUpdate(Menu::fireUpdateConfiguration, this)
{
	if(m_background)
	{
		m_background->setParent(this);
		m_drawables.push_back(m_background);
		m_background->setUpdateFocus(false);
	}

	if(m_title)
	{
		glm::vec3 titleSize = m_title->getDefaultSize() * m_title->getScale();
		m_title->setParent(this);
		m_title->setPosition(glm::vec3(0, -titleSize.y, 0));
		m_drawables.push_back(m_title);
		m_title->setUpdateFocus(false);
	}

	if(m_title)
	{
		if(m_background)
		{
			m_background->setPosition(glm::vec3(0, 0, 0));

			glm::vec3 s(1.0f);
			glm::vec3 bDefaultSize = m_background->getDefaultSize();
			glm::vec3 size         = m_title->getDefaultSize() * m_title->getScale();

			if(bDefaultSize.x != 0)
				s.x = size.x / bDefaultSize.x;
			if(bDefaultSize.y != 0)
				s.x = size.y / bDefaultSize.y;

			m_background->setScale(s);
			m_background->setPosition(glm::vec3(0.0f, -size.y, 0.0f));
		}
	}

	else if(m_background)
	{
		m_background->setCanDraw(false);		
	}
}

void Menu::addItemMenu(ItemMenu* itemMenu)
{
	glm::vec2 size(0, 0);
	glm::vec3 g;
	//Size of previous items
	for(ItemMenu* item : m_itemsMenu)
	{
		g = item->getDefaultSize() * item->getScale();
		size.x = fmax(size.x, g.x);
		size.y += g.y;
	}

	//Size of the title
	if(m_title)
	{
		g = m_title->getDefaultSize() * m_title->getScale();
		size.x = fmax(size.x, g.x);
		size.y += g.y;
	}

	//Size of this item
	g = itemMenu->getDefaultSize() * itemMenu->getScale();
	size.x = fmax(size.x, g.x);
	size.y += g.y;

	itemMenu->setPosition(glm::vec3(0, -size.y, 0));
	itemMenu->setParent(this);
	m_itemsMenu.push_back(itemMenu);
	m_drawables.push_back(itemMenu);

	if(m_background)
	{
		glm::vec3 s(1.0f);
		glm::vec3 bDefaultSize = m_background->getDefaultSize();

		if(bDefaultSize.x != 0)
			s.x = size.x / bDefaultSize.x;
		if(bDefaultSize.y != 0)
			s.y = size.y / bDefaultSize.y;

		m_background->setScale(s);
		m_background->setPosition(glm::vec3(0.0, -size.y, 0.0));
	}

	itemMenu->setUpdateConfig(&m_fireUpdate);

	setDefaultSize(glm::vec3(size.x, size.y, 0.0f));
	setDefaultPos(glm::vec3(0, -size.y, 0.0f));
}

Rectangle3f Menu::getDefaultConf() const
{
	glm::vec2 size(0, 0);
	glm::vec3 g;
	for(ItemMenu* item : m_itemsMenu)
	{
		g = item->getDefaultSize() * item->getScale();
		size.x = fmax(size.x, g.x);
		size.y += g.y;
	}

	if(m_title)
	{
		g = m_title->getDefaultSize() * m_title->getScale();
		size.x = fmax(size.x, g.x);
		size.y += g.y;
	}

	return Rectangle3f(getDefaultPos(), glm::vec3(size.x, size.y, 0.0f));
}

void Menu::updateConfiguration()
{

}

void Menu::fireUpdateConfiguration(void* menu)
{
	((Menu*)menu)->updateConfiguration();
}

void Menu::onFocus(uint32_t pe, Render& r)
{
}
