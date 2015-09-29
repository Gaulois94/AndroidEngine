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

class Explosion;

/** \brief The renderer class. It is a representative of the screen. */
class Renderer
{
	public:
		/** \brief create an uninitialized renderer */
		Renderer();
		virtual ~Renderer();

		/** \brief initialise the renderer's context
		 * \param window the android screen
		 * \return tell if the initialisation is successful */
		bool initializeContext(ANativeWindow* window);

		/** \brief initialise the renderer's surface
		 * \param window the android screen*/
		void initializeSurface(ANativeWindow *window);

		/** \brief update the screen*/
		bool display();

		/** \brief clear the screen*/
		void clear();

		/** \brief delete the current surface of the screen*/
		void deleteSurface();

		/** \brief tell if the renderer has a display where it can draw to. 
		 * \return return if it has a display where it can draw to.*/
		bool hasDisplay();

		/** \brief get the renderer camera
		 * \return the renderer camera*/
		Camera* getCamera();
		Color getAmbientColor();
	private:
		void terminate();
		EGLDisplay m_disp;
		EGLSurface m_surface;
		EGLContext m_context;
		EGLConfig m_conf;

		EGLint m_nbConf;
		EGLint m_format;

		Camera m_camera;

		int m_width;
		int m_height;
		bool m_start;
		ANativeWindow *m_window;
};

#endif
