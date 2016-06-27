#ifndef  ITEMMENU_INC
#define  ITEMMENU_INC

#include "Drawable.h"
#include "Widgets/FireUpdate.h"
#include "Widgets/Active.h"

class ItemMenu : public Drawable, Active
{
	public:
		ItemMenu(Updatable* parent, Drawable* item);
		const glm::vec3& getDefaultSize();
		void addUpdateConfig(FireUpdate* fu);
		void onDraw(Render& render, const glm::mat4& mvp);
		void onFocus(uint32_t pointerEvent, Render& render);
	private:
		Drawable* m_item;
		FireUpdate* m_updateConfig = NULL;		
};

#endif
