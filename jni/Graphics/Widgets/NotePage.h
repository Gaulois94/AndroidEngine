#ifndef  NOTEPAGE_INC
#define  NOTEPAGE_INC

#include "Drawable.h"
#include "Text.h"

class NotePage : public Drawable
{
	public:
		NotePage(Updatable* parent, Material* material, const Rectangle3f& rect);
};

#endif   /* ----- #ifndef NOTEPAGE_INC  ----- */
