#include "Renderer.h"

Renderer::Renderer() : m_disp(EGL_NO_CONTEXT), m_surface(EGL_NO_SURFACE), m_context(EGL_NO_CONTEXT), m_conf(0), m_nbConf(0), m_format(0), m_width(0), m_window(0)
{
	m_camera = glm::mat4(1.0);
}

Renderer::~Renderer()
{
	deleteSurface();
}

bool Renderer::initialize(ANativeWindow* window)
{
	if(window == NULL)
		return false;
	m_window = window;
	m_start = false;
	//Initialize the egl context
	const EGLint attribs[] = 
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_NONE
	};

	if((m_disp = eglGetDisplay(EGL_DEFAULT_DISPLAY))==EGL_NO_DISPLAY)
	{
		LOG_ERROR("Can't get the default display. Error : %d", eglGetError());
		return false;
	}

	if(!eglInitialize(m_disp, NULL, NULL))
	{
		LOG_ERROR("Can't init the egl buffer. Error : %d", eglGetError());
		return false;
	}

	if(!eglChooseConfig(m_disp, attribs, &m_conf, 1, &m_nbConf))
	{
		LOG_ERROR("Can't configure the buffer. Error : %d", eglGetError());
		return false;
	}

	if(!eglGetConfigAttrib(m_disp, m_conf, EGL_NATIVE_VISUAL_ID, &m_format))
	{
		LOG_ERROR("Can't get an attributes. Error : %d", eglGetError());
		return false;
	}

	if(!(m_surface = eglCreateWindowSurface(m_disp, m_conf, window, 0)))
	{
		LOG_ERROR("Can't create an EGL surface from this window. Error : %d", eglGetError());
		return false;
	}

	if(!(m_context = eglCreateContext(m_disp, m_conf, 0, 0)))
	{
		LOG_ERROR("Can't create an EGL context. Error : %d", eglGetError());
		return false;
	}

	if(!eglMakeCurrent(m_disp, m_surface, m_surface, m_context))
	{
		LOG_ERROR("Can't make this context the current one. Error : %d", eglGetError());
		return false;
	}

	ANativeWindow_setBuffersGeometry(window, 0, 0, m_format);

	eglQuerySurface(m_disp, m_surface, EGL_WIDTH, &m_width);
	eglQuerySurface(m_disp, m_surface, EGL_HEIGHT, &m_height);

	//Initialize OpenGL
	glViewport(0, 0, m_width, m_height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_start = true;
	return true;
}

bool Renderer::display()
{
	eglSwapBuffers(m_disp, m_surface);
	return true;
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::deleteSurface()
{
	if(m_disp == EGL_NO_DISPLAY)
		return;

	eglMakeCurrent(m_disp, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(m_disp, m_context);
	eglDestroySurface(m_disp, m_surface);

	m_surface = EGL_NO_SURFACE;
	m_context = EGL_NO_CONTEXT;
	eglTerminate(m_disp);
	m_disp = EGL_NO_DISPLAY;
}

bool Renderer::hasDisplay()
{
	return (m_disp != EGL_NO_DISPLAY);
}
