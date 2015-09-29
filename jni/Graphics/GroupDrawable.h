#ifndef DEF_GROUPDRAWABLE_INCLUDE
#define DEF_GROUPDRAWABLE_INCLUDE

#include "Drawable.h"
#include "Materials/Material.h"
#include "ResourcesManager.h"

/** \brief Contain a list of drawables.*/
class GroupDrawable : public Drawable
{
	public:
		/** \brief Init the GroupDrawable with the same material for each drawables.
		 * \param material The drawables material.*/
		GroupDrawable(Material* material);

		/** \brief Call each Drawable's onDraw function contained in the GroupDrawable.
		 * \param renderer The renderer where each drawable will be drawn on.
		 * \param mvp The transformation matrix for each drawable.*/
		void onDraw(Renderer* renderer, glm::mat4& mvp);

		/** \brief Set the material for all the object.
		 * \param the Drawables material.*/
		void setMaterial(Material* material); 

		/** \brief Get the ResourcesManager's drawables.
		 * \return the drawable's ResourcesManager.*/
		ResourcesManager<Drawable*> getDrawables(); //Return the list of drawables
	protected:
		ResourcesManager<Drawable*> m_drawables; //The list of drawables
};

#endif
