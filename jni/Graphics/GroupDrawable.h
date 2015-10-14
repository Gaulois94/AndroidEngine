#ifndef DEF_GROUPDRAWABLE_INCLUDE
#define DEF_GROUPDRAWABLE_INCLUDE

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "Drawable.h"
#include "Materials/Material.h"
#include "ResourcesManager.h"

/** \brief Contain a list of drawables. These drawable are only a part of a bigger one, that's why it exists with the Updatable class*/
class GroupDrawable : public Drawable
{
	public:
		/** \brief Init the GroupDrawable with the same material for each drawables.
		 * \param material The drawables material.
		 * \param parent its parent
		 * \param material The drawables material.
		 * \param defaultConf The default configuration (pos and size) of the GroupDrawable*/
		GroupDrawable(Updatable* parent, Material* material, const Rectangle3f& defaultConf);

		void update(Render& render);

		/** \brief Call each Drawable's draw function contained in the GroupDrawable.
		 * \param render The Render where each drawable will be drawn on.
		 * \param transformation The transformation matrix for each drawable.*/
		void onDraw(Render& render, const glm::mat4& transformation=glm::mat4(1.0f));

		/** \brief Set the material for all the object.
		 * \param the Drawables material.*/
		void setMaterial(Material* material); 

		/** \brief Set the staticity of all the sub drawables
		 * \param s the staticity*/
		void staticToCamera(bool s);

		/** \brief Get the ResourcesManager's drawables.
		 * \return the drawable's ResourcesManager.*/
		ResourcesManager<Drawable*> getDrawables(); //Return the list of drawables
	protected:
		ResourcesManager<Drawable*> m_drawables; //The list of drawables
};

#endif
