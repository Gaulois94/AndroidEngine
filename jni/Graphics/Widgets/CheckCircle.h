#ifndef  CHECKCIRCLE_INC
#define  CHECKCIRCLE_INC

#include "Graphics/Shape/Circle.h"
#include "Graphics/GroupDrawable.h"
#include "Graphics/Widgets/Active.h"

/** \brief CheckCircle class. Used by RadioButton.*/
class CheckCircle : public GroupDrawable, Active
{
	public:
		/** \brief default constructor
		 * \param parent its parent
		 * \param littleMtl the Material of the little Circle
		 * \param bigMtl the Material of the big Circle
		 * \param radius the radius of the big Circle
		 * \param nbEdge the edge of the circles*/
		CheckCircle(Updatable* parent, Material* littleMtl, Material* bigMtl, float radius, uint32_t nbEdge=16);
		void onFocus(Render& render);

		/** \brief set the Material of the little Circle
		 * \param mtl the new Material*/
		void setLittleMtl(Material* mtl);

		/** \brief set the Material of the big Circle
		 * \param mtl the new Material*/
		void setBigMtl(Material* mtl);

		void onFocus();
		void activeIt();
		void disactiveIt();
	private:
		Circle m_littleCircle;
		Circle m_bigCircle;
};

#endif   /* ----- #ifndef CHECKCIRCLE_INC  ----- */
