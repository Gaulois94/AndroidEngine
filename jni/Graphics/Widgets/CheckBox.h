#ifndef DEF_CASEBOX
#define DEF_CASEBOX

#include "Widgets/Widget.h"
#include "Active.h"
#include "Shape/TriangleShape.h"
#include "Shape/Rectangle.h"
#include "GroupDrawable.h"

/** \brief CheckBox class. Use to create CheckBox*/
class CheckBox : public Widget, public Active, public GroupDrawable
{
	public:
		/** \brief CheckBox constructor. Create a Rectangle and a cross
		 * \param parent its parent
		 * \param material its material. Normally it is useless, then select setCrossMaterial and setRectangleMaterial function.
		 * \param size its size. Default position at (0, 0)*/
		CheckBox(Updatable* parent, Material* material, const glm::vec2& size);

		virtual void onUpdate(Render &render);
		virtual void draw(Render &render, const glm::mat4& transformation=glm::mat4(1.0f));

		/** \brief set the cross material.
		 * \param material the cross material*/
		void setCrossMaterial(Material* material);

		/** \brief set the Rectangle Material
		 * \param material the new Rectangle Material*/
		void setRectangleMaterial(Material* material);

		/** \brief Currently, Checkbox's can't never be selected
		 * \return currently, return false*/
		bool howSelect();

		/** \brief activated when it is not activated(m_active = false) and it is toggled
		 * \brief return if the requirements of the activement are fulfill*/
		bool howActive();

		/** \brief Currently, Checkbox's can't never be deselected
		 * \return currently, return false*/
		bool howDeselect();
		void howDisactive();
	private:
		Rectangle* m_rectangle;
		TriangleShape* m_cross;
};

#endif
