#ifndef DEF_RENDER_INCLUDE
#define DEF_RENDER_INCLUDE

#include "Drawable.h"
#include "Camera.h"

/** \brief basic class Render. Use to put in common all classes used to draw something on texture, and update it*/
class Render
{
	public:
		/** \brief Constructor of Render. Do nothing.*/
		Render();

		/** \brief function draw. It init the draw function, call Drawable's call function, and use stopDraw function
		 * \param drawable the object being drawn
		 * \param transformation could apply a transformation to the Drawable object before being drawn.*/
		virtual void draw(Drawable& drawable, const glm::mat4& transformation=glm::mat4(1.0));

		/** \brief draw all the information got by draw function*/
		virtual void display()=0;

		/** \brief init the draw function */
		virtual void initDraw()=0;

		/** \brief stop the capacity to draw to the Render's texture*/
		virtual void stopDraw()=0;

		/** \brief clear the buffer where the Render is associated (the screen, a texture, etc...)*/
		virtual void clear()=0;

		/** \brief get the Render camera*/
		Camera& getCamera();
	private:
		Camera m_camera;
};

#endif
