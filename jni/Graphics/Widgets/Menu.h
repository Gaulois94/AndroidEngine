#ifndef  MENU_INC
#define  MENU_INC

#define GLM_FORCE_RADIANS
#include "GroupDrawable.h"
#include "Widgets/ItemMenu.h"
#include "Widgets/Alignment.h"

class Menu : public Drawable
{
	public:
		/** \brief create a Menu with a title "title". The drawable can be what ever you want.
		 * \param parent the Updatable parent
		 * \param title a Drawable which will be on the top of the Menu. Naturally, its parent will be set.
		\param background the background of the Menu. It's parent and transformation will be automatically set.*/
		Menu(Updatable* parent, Drawable* title, const glm::vec3& defPos=glm::vec3(0, 0, 0), Drawable* background = NULL);

		/** \brief Add an ItemMenu.
		 * \param itemMenu the ItemMenu to be adding. It's transformation matrix will be automatically set, with it's parent*/
		void addItemMenu(ItemMenu* itemMenu);

		Rectangle3f getDefaultConf() const;
		void onFocus(uint32_t, Render&);
		void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));

		/** \brief set the alignement of ItemMenu. Default : BOTTOM_RIGHT
		 * \param alignement The new ItemMenu alignement*/
		void setItemAlignment(XAlignment alignement);
	private:
		void updateConfiguration();
		static void fireUpdateConfiguration(Active* item, void* menu);

		Drawable* m_title;
		std::vector<ItemMenu*> m_itemsMenu;
		Drawable* m_background;
		ActiveListener m_activeListener;

		XAlignment m_itemOrigin = X_LEFT;
};

#endif
