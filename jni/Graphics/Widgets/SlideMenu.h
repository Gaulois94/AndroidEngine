#ifndef  SLIDEMENU_INC
#define  SLIDEMENU_INC

#define GLM_FORCE_RADIANS
#include "Drawable.h"
#include "Widgets/ItemMenu.h"
#include "Widgets/Menu.h"
#include "Widgets/ScrollWidget.h"

class SlideMenu : public Drawable
{
	/** \brief The Status of the SlideMenu (menu hidden or showed)*/
	enum Status {ON, OFF};
	public:
		/** \brief create a SlideMenu
		 * \param parent the parent of the Widget 
		 * \param maxSize the size used to clip the Widget when the menu is ON
		 * \param backgroundItem the Drawable drawn just before the active item
		 * \param backgroundMenu the Drawable drawn behind the SlideMenu while in activation*/
		SlideMenu(Updatable* parent, float height, Drawable* backgroundItem=NULL, Drawable* backgroundMenu = NULL);

		~SlideMenu();

		/** \brief add the drawable to the SliderMenu
		 * \param im the ItemMenu to add. Do not change its matrix transformation after that*/
		void addItemMenu(ItemMenu* im);

		/** \brief add a Text entry at the end of the SlideMenu. Useful if you won't handle a Drawable object
		 * \param m the Material of the new object
		 * \param f the Font of the object
		 * \param t the Text of the object*/
		void addText(Material* m, Font* f, const std::string& t, const glm::vec3& imediatScale = glm::vec3(1.0, 1.0, 1.0));

		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f)){}
	private:
		//----------------------Private functions-------------------------//
		/** \brief update the configuration of the menu (item matrix)*/
		void updateConfiguration();

		/** \brief the callback of the listener
		 * \param a the ItemMenu activated
		 * \param data the data sent*/
		static void listenerCallback(Active* a, void* data);

		//----------------------Private attributs-------------------------//
		ScrollWidget           m_scrollWidget;
		Menu                   m_hiddenMenu;
		ItemMenu*              m_itemMenu=NULL;
		std::vector<Text*>     m_textsCreated;
		std::vector<ItemMenu*> m_dynEntries;
		Drawable*              m_backgroundActive;
		ActiveListener         m_itemListener;
		Status                 m_status = OFF;
		float                  m_height;
};

#endif
