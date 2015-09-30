#ifndef DEF_WIDGET
#define DEF_WIDGET

#include "Drawable.h"

/** \brief basic class for all the widgets*/
class Widget : public Drawable
{
	public:
		/** \brief Widget constructor. Initialise its material and its parent
		 * \param parent the Widget's parent (could be NULL)
		 * \param material the Widget's material (could be NULL)*/
		Widget(Updatable* parent, Material* material);
}

#endif
