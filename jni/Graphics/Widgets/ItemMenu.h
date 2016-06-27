#ifndef  ITEMMENU_INC
#define  ITEMMENU_INC

#include "Drawable.h"
#include "Listeners/ActiveListener.h"
#include "Widgets/Active.h"

class ItemMenu : public Drawable, Active
{
	public:
		ItemMenu(Updatable* parent, Drawable* item);
		const glm::vec3& getDefaultSize();
		void setUpdateConfig(const ActiveListener& fu);
		void onDraw(Render& render, const glm::mat4& mvp);
		void onFocus(uint32_t pointerEvent, Render& render);
	private:
		Drawable* m_item;
		ActiveListener m_updateConfig;		
};

#endif
