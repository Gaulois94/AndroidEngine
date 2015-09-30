#ifndef DEF_WIDGET
#define DEF_WIDGET

#include "Drawable.h"

/** \brief basic class for all the widgets.
 * Because a Widget could be composed of many sub drawables, it is considerated as a GroupDrawable*/
class Widget : public GroupDrawable
{
	public:
		/** \brief Widget constructor. Initialise its material and its parent
		 * \param parent the Widget's parent (could be NULL)
		 * \param material the Widget's material (could be NULL)*/
		Widget(Updatable* parent, Material* material);
}

#endif
