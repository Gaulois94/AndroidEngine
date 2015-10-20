#ifndef DEF_CASEBOX
#define DEF_CASEBOX

#include "Active.h"
#include "Shape/TriangleShape.h"
#include "Shape/Rectangle.h"
#include "GroupDrawable.h"

/** \brief CheckBox class. Use to create CheckBox*/
class CheckBox : public Active, public GroupDrawable
{
	public:
		/** \brief CheckBox constructor. Create a Rectangle and a cross
		 * \param parent its parent
		 * \param material its material. Normally it is useless, then select setCrossMaterial and setRectangleMaterial function.
		 * \param size its size. Default position at (0, 0)*/
		CheckBox(Updatable* parent, Material* material, const glm::vec2& size);

		~CheckBox();

		virtual void onFocus(Render& render);
		virtual void onUpdate(Render &render);

		/** \brief set the cross material.
		 * \param material the cross material*/
		void setCrossMaterial(Material* material);

		/** \brief set the Rectangle Material
		 * \param material the new Rectangle Material*/
		void setRectangleMaterial(Material* material);

		void activeIt();
		void disactiveIt();
	private:
		Rectangle* m_rectangle;
		TriangleShape* m_cross;
};

#endif
