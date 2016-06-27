#include "Widgets/ItemMenu.h"

ItemMenu::ItemMenu(Updatable* parent, Drawable* item) : Drawable(parent, NULL, item->getDefaultConf()), Active(), m_item(item)
{
	item->setParent(this);
	item->setApplyTransformation(this);
	item->setUpdateFocus(false);
}

const glm::vec3& ItemMenu::getDefaultSize()
{
	return m_item->getDefaultSize();
}

void ItemMenu::setUpdateConfig(const ActiveListener& fu)
{
	m_updateConfig = fu;
}

void ItemMenu::onDraw(Render& render, const glm::mat4& mvp){}

void ItemMenu::onFocus(uint32_t pointerEvent, Render& render)
{
	if(m_isActive)
		disactiveIt();
	else
		activeIt();
}
