#include "Widgets/ItemMenu.h"

ItemMenu::ItemMenu(Updatable* parent, Drawable* item) : Drawable(parent, NULL, item->getDefaultConf()), Active(), m_item(item)
{
	item->setParent(this);
	item->setApplyTransformation(this);
	item->setUpdateFocus(false);
	setDefaultSize(m_item->getRect().getSize());
}

void ItemMenu::setUpdateConfig(const ActiveListener& fu)
{
	m_updateConfig = fu;
}

void ItemMenu::onDraw(Render& render, const glm::mat4& mvp){}

void ItemMenu::onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp)
{
	activeIt();
	m_isActive = false;
}
