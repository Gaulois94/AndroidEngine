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

class Renderer
{
	public:
		Renderer();
		virtual ~Renderer();

		bool initializeContext(ANativeWindow* window);
		void initializeSurface(ANativeWindow *window);
		bool display();
		void clear();
		void deleteSurface();
		bool hasDisplay();

		Camera* getCamera();
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
