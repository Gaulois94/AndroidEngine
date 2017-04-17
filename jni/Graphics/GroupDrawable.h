#ifndef DEF_GROUPDRAWABLE_INCLUDE
#define DEF_GROUPDRAWABLE_INCLUDE

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "Drawable.h"
#include "Materials/Material.h"

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

		~GroupDrawable();

		void onUpdate(Render& render);

		/** \brief Call each Drawable's draw function contained in the GroupDrawable and its own onDraw function
		 * \param render The Render where each drawable will be drawn on.
		 * \param transformation The transformation matrix for each drawable.*/
		void draw(Render& render, const glm::mat4& transformation=glm::mat4(1.0f));

		void onDraw(Render& render, const glm::mat4& transformation=glm::mat4(1.0f));

		/** \brief Set the material for all the object.
		 * \param the Drawables material.*/
		void setMaterial(Material* material); 

		/** \brief Set the staticity of all the sub drawables
		 * \param s the staticity*/
		void staticToCamera(bool s);

		/** \brief Get the ResourcesManager's drawables.
		 * \return the drawable's ResourcesManager.*/
		std::list<Drawable*> getDrawables(); //Return the list of drawables

	protected:
		/** \brief Add a sub drawable to the Object.
		 * \param d the Drawable to add
		 * \param pos the position of the Drawable in the list (number greater than the number of Drawable own by the Object of inferior at 0 will be pushed at the end)*/
		void addSubDrawable(Drawable* d, int pos=-1);

		/** \brief Delete a Drawable own by the Object
		 * \param d The Drawable to remove from the list*/
		void deleteSubDrawable(Drawable* d);

		/** \brief Delete a Drawable own by the Object
		 * \param pos The position of the Drawable in the list. number inferior at 0 or greater than the size of drawables own by the Object is consider as the end of the list.*/
		void deleteSubDrawable(int pos=-1);

		/** \brief Should we delete the Drawable in the Destructor ?
		 * \param del the new value*/
		void deleteAuto(bool del);

		bool m_deleteAuto;
		std::list<Drawable*> m_drawables; //The list of drawables
};

#endif
