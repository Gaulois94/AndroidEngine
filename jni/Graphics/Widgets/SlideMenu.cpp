#include "Widgets/SlideMenu.h"

SlideMenu::SlideMenu(Updatable* parent, const Vector2f& maxSize, Drawable* backgroundItem, Drawable* backgroundMenu) : Drawable(parent, NULL, Rectangle3f(glm::vec3(0, 0, 0) ,glm::vec3(0, 0, 0))),
//	m_scrollWidget(this, Rectangle2f(0.0, 0.0, 1.0, 1.0), Rectangle3f(0.0, 0.0, 0.0, maxSize.x, maxSize.y, 0.0)),
	m_scrollWidget(this),
	m_hiddenMenu(&m_scrollWidget, NULL, glm::vec3(0.0, 0.0, 0.0), backgroundMenu),
   	m_backgroundActive(backgroundItem), m_itemListener(SlideMenu::listenerCallback, (void*)this)
{
	m_hiddenMenu.setActiveListener(&m_itemListener);
	m_scrollWidget.enableClipping(false);
	if(backgroundItem)
		addChild(backgroundItem);
//	m_scrollWidget.setCanUpdate(true);
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
	updateConfiguration();

	Rectangle3f hr = m_hiddenMenu.getDefaultConf();
	m_scrollWidget.setMaxBound(Rectangle2f(hr.x, hr.y, hr.width, hr.height));
//	m_scrollWidget.setMoveValue(Vector2f(0.0, 0.0));
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
		m_scrollWidget.setCanUpdate(true);

		//Show every item menu
		for(uint32_t i=0; i < m_hiddenMenu.getItems().size(); i++)
			m_hiddenMenu.getItems()[i]->setCanUpdate(true);

		m_scrollWidget.setMoveValue(Vector2f(0.0, 0.0));
	}

	else if(m_status == OFF)
	{
		m_itemMenu->setParent(NULL);
		m_scrollWidget.setCanUpdate(false);
		addChild(m_itemMenu, 1);

		//Hide everything except our item
		for(uint32_t i=0; i < m_hiddenMenu.getItems().size(); i++)
			m_hiddenMenu.getItems()[i]->setCanUpdate(false);
		m_itemMenu->setCanUpdate(true);

		m_scrollWidget.setMoveValue(Vector2f(0.0, -m_itemMenu->getPosition().y));
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
