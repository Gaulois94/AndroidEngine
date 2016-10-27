#ifndef DEF_RENDER_INCLUDE
#define DEF_RENDER_INCLUDE

#include "Transformable.h"
#include "Camera.h"
#include "Updatable.h"
#include "Color.h"

class Drawable;

/** \brief basic class Render. Use to put in common all classes used to draw something on texture, and update it*/
class Render : public Updatable
{
	public:
		/** \brief Constructor of Render. Do nothing.*/
		Render(Updatable* parent);

		~Render();

		/** \brief function draw. It init the draw function, call Drawable's call function, and use stopDraw function
		 * \param drawable the object being drawn
		 * \param transformation could apply a transformation to the Drawable object before being drawn.*/
		virtual void draw(Drawable& drawable, const glm::mat4& transformation=glm::mat4(1.0));

		/** \brief update all child focus with it as the Render object
		 * \param pointerEvent the indice of the Motion Event
		 * \param render the previous render object (for exemple a Renderer which call a RendererTexture)*/
		virtual void updateFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp = glm::mat4(1.0f));

		virtual void update(Render& render);
		virtual void updateGPU(Render& render);

		/** \brief draw all the information got by draw function*/
		virtual void display()=0;

		/** \brief init the draw function */
		virtual void initDraw()=0;

		/** \brief stop the capacity to draw to the Render's texture*/
		virtual void stopDraw()=0;

		/** \brief clear the buffer where the Render is associated (the screen, a texture, etc...)*/
		virtual void clear()=0;

		const Color& getAmbientColor() const;

		/** \brief get the Render camera*/
		Camera& getCamera();

		glm::vec3 getPositionOnScreen(const glm::vec3& p) const;
		Render* getRenderParent();
	protected:
		Color m_ambientColor;
		Camera m_camera;
};

#endif
