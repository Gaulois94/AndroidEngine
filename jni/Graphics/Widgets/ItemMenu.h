#ifndef  ITEMMENU_INC
#define  ITEMMENU_INC

#include "Drawable.h"
#include "Widgets/Active.h"

class ItemMenu : public Drawable, public Active
{
	public:
		ItemMenu(Updatable* parent, Drawable* item);
		void setUpdateConfig(const ActiveListener& fu);
		void onDraw(Render& render, const glm::mat4& mvp);
		void onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		const Drawable* getItem() const{return m_item;}
	private:
		Drawable* m_item;
		ActiveListener m_updateConfig;		
};

#endif
