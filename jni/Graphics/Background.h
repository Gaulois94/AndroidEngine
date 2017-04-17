#ifndef  BACKGROUND_INC
#define  BACKGROUND_INC

#include "GroupDrawable.h"

/** \brief Object which associate a background to a specific Drawable*/
class Background : public GroupDrawable
{
	public:
		/** \brief Constructor
		 * \param parent The parent of the Background
		 * \param theDrawable The Drawable to attach
		 * \param background The background to attach*/
		Background(Updatable* parent, Drawable* theDrawable, Drawable* background);

		/** \brief static function for internal use, do not call it*/
		static void changeDrawableRect(void* data);

		/** \brief Set the Drawable attached
		 * \param d the new Drawable to attach*/
		void setDrawable(Drawable* d);

		/** \brief Set the background attached
		 * \param b the new background to attach*/
		void setBackground(Drawable* b);
	private:
		void updateBackgroundRect();
		Drawable* m_drawable;
		Drawable* m_background;
		Callback  m_changeCallback;
};

#endif
