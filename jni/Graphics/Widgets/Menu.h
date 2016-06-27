#ifndef  MENU_INC
#define  MENU_INC

#define GLM_FORCE_RADIANS
#include "GroupDrawable.h"
#include "Widgets/ItemMenu.h"

class Menu : public GroupDrawable
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
	private:
		void updateConfiguration();
		static void fireUpdateConfiguration(Active* item, void* menu);

		Drawable* m_title;
		std::vector<ItemMenu*> m_itemsMenu;
		Drawable* m_background;
		ActiveListener m_activeListener;
};

#endif
