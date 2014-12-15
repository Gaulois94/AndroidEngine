#define GLM_FORCE_RADIANS

#include <GLES/gl.h>
#include <EGL/egl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <android/native_window.h>
#include "logger.h"

class Renderer
{
	public:
		Renderer();
		virtual ~Renderer();

		bool initialize(ANativeWindow *window);
		bool display();
		void clear();
		void deleteSurface();
		bool hasDisplay();
	private:
		EGLDisplay m_disp;
		EGLSurface m_surface;
		EGLContext m_context;
		EGLConfig m_conf;

		EGLint m_nbConf;
		EGLint m_format;

		glm::mat4 m_camera;

		int m_width;
		int m_height;
		bool m_start;
		ANativeWindow *m_window;
};
