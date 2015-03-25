#ifndef DEF_GROUPDRAWABLE_INCLUDE
#define DEF_GROUPDRAWABLE_INCLUDE

#include "Drawable.h"
#include "Materials/Material.h"
#include "ResourcesManager.h"

class GroupDrawable : public Drawable
{
	public:
		GroupDrawable(Material* material);
		void onDraw(Renderer* renderer, glm::mat4& mvp);
		void setMaterial(Material* material); //Set the material for all the object.
		ResourcesManager<Drawable*> getDrawables(); //Return the list of drawables
	protected:
		ResourcesManager<Drawable*> m_drawables; //The list of drawables
};

#endif
