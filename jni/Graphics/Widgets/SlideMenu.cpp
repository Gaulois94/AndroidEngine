#include "Widgets/SlideMenu.h"

SlideMenu::SlideMenu(Updatable* parent, float height, Drawable* backgroundItem, Drawable* backgroundMenu) : Drawable(parent, NULL, Rectangle3f(glm::vec3(0, 0, 0) ,glm::vec3(0, 0, 0))),
	m_scrollWidget(this, Rectangle2f(0.0, 0.0, 0.0, 0.0), Rectangle3f(0, -height, 0.0, 0.0, height, 0.0)),
	m_hiddenMenu(&m_scrollWidget, NULL, glm::vec3(0.0, 0.0, 0.0), backgroundMenu),
   	m_backgroundActive(backgroundItem), m_itemListener(SlideMenu::listenerCallback, (void*)this),
	m_height(height)
{
	m_hiddenMenu.setActiveListener(&m_itemListener);
	if(backgroundItem)
		addChild(backgroundItem);
	m_scrollWidget.setCanUpdate(true);
	m_scrollWidget.setApplyTransformation(this);
}

SlideMenu::~SlideMenu()
{
	for(uint32_t i=0; i < m_textsCreated.size(); i++)
		delete m_textsCreated[i];

	for(uint32_t i=0; i < m_dynEntries.size(); i++)
		delete m_dynEntries[i];
}

void SlideMenu::addItemMenu(ItemMenu* im)
{
	m_hiddenMenu.addItemMenu(im);

	Rectangle3f hr = m_hiddenMenu.getDefaultConf();
	m_scrollWidget.setDefaultConf(Rectangle3f(hr.x, -m_height, hr.z, hr.width, m_height, hr.depth));
	m_scrollWidget.setMoveValue(Vector2f(0.0, 0.0));

	Vector2f maxSize = m_hiddenMenu.getMaxItemSize();
	setDefaultSize(glm::vec3(maxSize.x, maxSize.y, 0.0));
	setDefaultPos(glm::vec3(0.0, -maxSize.y, 0.0));

	updateConfiguration();
}

void SlideMenu::addText(Material* m, Font* f, const std::string& t, const glm::vec3& defScale)
{
	Text* te      = new Text(NULL, m, f, t.c_str());
	ItemMenu* ie  = new ItemMenu(this, te);
	ie->setScale(defScale);

	addItemMenu(ie);

	m_textsCreated.push_back(te);
	m_dynEntries.push_back(ie);
}

void SlideMenu::updateConfiguration()
{
	if(m_itemMenu == NULL)
		m_itemMenu = (m_hiddenMenu.getItems()[0]);

	if(m_status == ON)
	{
		m_scrollWidget.setActiveScroll(true);

		//Show every item menu
		for(uint32_t i=0; i < m_hiddenMenu.getItems().size(); i++)
			m_hiddenMenu.getItems()[i]->setCanUpdate(true);

		Rectangle3f hr = m_hiddenMenu.getDefaultConf();
		m_scrollWidget.setMaxBound(Rectangle2f(0.0, 0.0, 0.0, fmax(0.0, hr.height - m_height)));
		m_scrollWidget.setMoveValue(Vector2f(0.0, 0.0));
	}

	else if(m_status == OFF)
	{
		m_scrollWidget.setActiveScroll(false);

		//Hide everything except our item
		for(uint32_t i=0; i < m_hiddenMenu.getItems().size(); i++)
			m_hiddenMenu.getItems()[i]->setCanUpdate(false);
		m_itemMenu->setCanUpdate(true);

		Rectangle3f r = m_itemMenu->getRect();
		m_scrollWidget.setMaxBound(Rectangle2f(0.0, 0.0, 0.0, -m_itemMenu->getPosition().y - r.height));
		m_scrollWidget.setMoveValue(Vector2f(0.0, -m_itemMenu->getPosition().y - r.height));
	}
}

void SlideMenu::listenerCallback(Active* a, void* data)
{
	SlideMenu* self = (SlideMenu*)data;
	self->m_itemMenu = (ItemMenu*)a;
	if(self->m_status == ON)
		self->m_status = OFF;
	else
		self->m_status = ON;
	self->updateConfiguration();
}

void const ItemMenu* SlideMenu::getActiveItemMenu() const
{
	return m_itemMenu;
}


void int SlideMenu::getActiveNbItemMenu() const
{
	for(uint32_t i=0; i < m_hiddenMenu.getItems().size(); i++)
		if(m_hiddenMenu.getItems()[i] == m_itemMenu)
			return i;
	return -1;
}
