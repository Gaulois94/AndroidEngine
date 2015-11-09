#ifndef DEF_RENDERER_INCLUDE
#define DEF_RENDERER_INCLUDE

#define GLM_FORCE_RADIANS

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <android/native_window.h>
#include "logger.h"
#include "Camera.h"
#include "Color.h"
#include "Render.h"
#include "EventManager.h"
#include "Rectangle2.h"
#include "Shape/Circle.h"

/** \brief The renderer class. It is a representative of the screen. */
class Renderer : public Render
{
	public:
		/** \brief create an uninitialized renderer */
		Renderer(Updatable* parent);
		virtual ~Renderer();

		/** \brief initialise the renderer's context
		 * \param window the android screen
		 * \return tell if the initialisation is successful */
		bool initializeContext(ANativeWindow* window);

		/** \brief initialise the renderer's surface
		 * \param window the android screen*/
		void initializeSurface(ANativeWindow *window);

		/** \brief update the full screen*/
		void display();

		/** \brief clear the full screen*/
		void clear();

		/** \brief function called when the Renderer could init all its children Drawable (because the android on the java side should init things before) */
		void init();

		void update(Render& render);
		void updateFocus();
		void initDraw();
		void stopDraw();

		//Events function
		
		/** \brief function called when the Renderer is released. Called by the View which contain the Renderer (from the Renderer java class for example, or a C++ native activity)
		 * \param x the x coord in opengl format
		 * \param y the y coord in opengl format*/
		void onUpTouchEvent(float x, float y);

		/** \brief function called when the Renderer is touched. Called by the View which contain the Renderer (from the Renderer java class for example, or a C++ native activity)
		 * \param x the x coord in opengl format
		 * \param y the y coord in opengl format*/
		void onDownTouchEvent(float x, float y);

		/** \brief function called when the Renderer is touched and the (x, y) coords are changing. Called by the View which contain the Renderer (from the Renderer java class for example, or a C++ native activity)
		 * \param x the x coord in opengl format
		 * \param y the y coord in opengl format*/
		void onMoveTouchEvent(float x, float y);

		void accelerometerEvent(float x, float y, float z);

		/** \brief delete the current surface of the screen*/
		void deleteSurface();

		/** \brief tell if the renderer has a display where it can draw to. 
		 * \return return if it has a display where it can draw to.*/
		bool hasDisplay();
	private:
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
};

#endif
