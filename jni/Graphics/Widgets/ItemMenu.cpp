#include "Widgets/ItemMenu.h"

ItemMenu::ItemMenu(Updatable* parent, Drawable* item) : Drawable(parent, NULL, item->getDefaultConf()), Active(), m_item(item)
{
	item->setParent(this);
	item->setApplyTransformation(this);
	item->setUpdateFocus(false);
	setDefaultSize(m_item->getDefaultSize() * m_item->getScale());
	LOG_ERROR("%f, %f", getDefaultSize().x, getDefaultSize().y);
}

void ItemMenu::setUpdateConfig(const ActiveListener& fu)
{
	m_updateConfig = fu;
}

void ItemMenu::onDraw(Render& render, const glm::mat4& mvp){}

void ItemMenu::onFocus(uint32_t pointerEvent, Render& render)
{
	activeIt();
	m_isActive = false;
}
