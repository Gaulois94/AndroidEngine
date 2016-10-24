#ifndef DEF_RENDERER_INCLUDE
#define DEF_RENDERER_INCLUDE

#define GLM_FORCE_RADIANS

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "jni.h"

#include <android/native_window.h>
#include "logger.h"
#include "Camera.h"
#include "Color.h"
#include "Render.h"
#include "EventManager.h"
#include "Rectangle2.h"
#include "Shape/Circle.h"
#include "Materials/UniColorMaterial.h"
#include "Keyboard.h"
#include "Event.h"

/** \brief The renderer class. It is a representative of the screen. */
class Renderer : public Render
{
	public:
		/** \brief create an uninitialized renderer */
		Renderer(Updatable* parent);
		virtual ~Renderer();

		/** \brief initialise the renderer's context
		 * \return tell if the initialisation is successful */
		bool initializeContext();

		void releaseSurface();

		/** \brief initialise the renderer's surface
		 * \param window the android screen*/
		void initializeSurface(ANativeWindow *window);

		/** \brief update the full screen*/
		virtual void display();

		/** \brief clear the full screen*/
		virtual void clear();

		/** \brief function called when the Renderer could init all its children Drawable (because the android on the java side should init things before) */
		virtual void init();

		void update(Render& render);
		/* *\brief update all child function with it as Render object*/
		void updateFocus(const TouchEvent& te);
		virtual void initDraw();
		virtual void stopDraw();

		//Events function

		virtual bool keyUpEvent(int32_t keyCode);
		virtual bool keyDownEvent(int32_t keyCode);
		
		/** \brief function called when the Renderer is released. Called by the View which contain the Renderer (from the Renderer java class for example, or a C++ native activity)
		 * \param indice the indice pointer to the touch Event
		 * \param x the x coord in opengl format
		 * \param y the y coord in opengl format*/
		virtual void onUpTouchEvent(uint32_t indice, float x, float y);

		/** \brief function called when the Renderer is touched. Called by the View which contain the Renderer (from the Renderer java class for example, or a C++ native activity)
		 * \param indice the indice pointer to the touch Event
		 * \param x the x coord in opengl format
		 * \param y the y coord in opengl format*/
		virtual void onDownTouchEvent(uint32_t indice, float x, float y);

		/** \brief function called when the Renderer is touched and the (x, y) coords are changing. Called by the View which contain the Renderer (from the Renderer java class for example, or a C++ native activity)
		 * \param indice the indice pointer to the touch Event
		 * \param x the x coord in opengl format
		 * \param y the y coord in opengl format*/
		virtual void onMoveTouchEvent(uint32_t indice, float x, float y);

		virtual void accelerometerEvent(float x, float y, float z);

		/** \brief delete the current surface of the screen*/
		void deleteSurface();

		virtual void setViewport(int width, int height);

		/** \brief tell if the renderer has a display where it can draw to. 
		 * \return return if it has a display where it can draw to.*/
		bool hasDisplay();

		/** \brief show the keyboard
		 * \param show show the keyboard or hide it*/
		void showKeyboard(bool show);
	protected:
		void terminate();
		EGLDisplay m_disp;
		EGLSurface m_surface;
		EGLContext m_context;
		EGLConfig m_conf;

		EGLint m_nbConf;
		EGLint m_format;

		int m_width;
		int m_height;
		bool m_start;
		ANativeWindow *m_window;

		std::list<Event*> m_events;
};

#endif
