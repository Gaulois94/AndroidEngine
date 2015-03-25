#include "Renderer.h"
#include "Shape/Cylinder.h"
#include "Shape/Sphere.h"
#include "Materials/ObjMaterial.h"
#include "Materials/UniColorMaterial.h"

Renderer::Renderer() : m_disp(EGL_NO_CONTEXT), m_surface(EGL_NO_SURFACE), m_context(EGL_NO_CONTEXT), m_conf(0), m_nbConf(0), m_format(0), m_width(0), m_window(0)
{
}

Renderer::~Renderer()
{
	terminate();
}

void Renderer::terminate()
{
	if(m_disp == EGL_NO_DISPLAY)
		return;

	eglReleaseThread();
	eglMakeCurrent(m_disp, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(m_disp, m_context);
	eglDestroySurface(m_disp, m_surface);

	m_surface = EGL_NO_SURFACE;
	m_context = EGL_NO_CONTEXT;
	eglTerminate(m_disp);
	m_disp = EGL_NO_DISPLAY;
}

bool Renderer::initializeContext(ANativeWindow* window)
{
	m_start = false;
	m_window = window;
	terminate();

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

	const EGLint eglAttribs[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
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


	if(!(m_context = eglCreateContext(m_disp, m_conf, 0, eglAttribs)))
	{
		LOG_ERROR("Can't create an EGL context. Error : %d", eglGetError());
		return false;
	}

	initializeSurface(window);

	return true;
}

void Renderer::initializeSurface(ANativeWindow* window)
{
	if(window == NULL)
		return;
	deleteSurface();
	m_window = window;
	m_start = false;

	if(!(m_surface = eglCreateWindowSurface(m_disp, m_conf, window, 0)))
	{
		LOG_ERROR("Can't create an EGL surface from this window. Error : %d", eglGetError());
		return;
	}

	if(!eglMakeCurrent(m_disp, m_surface, m_surface, m_context))
	{
		LOG_ERROR("Can't make this context the current one. Error : %d", eglGetError());
		initializeSurface(window);
		return;
	}

	ANativeWindow_setBuffersGeometry(window, 0, 0, m_format);

	eglQuerySurface(m_disp, m_surface, EGL_WIDTH, &m_width);
	eglQuerySurface(m_disp, m_surface, EGL_HEIGHT, &m_height);

	//Initialize OpenGL
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_start = true;
}

bool Renderer::display()
{
	ObjMaterial m(Color::BLUE, Color::WHITE);
	m_camera.setPosition(glm::vec3(0.0, 0.0, 1.5));
	m_camera.rotate(PI/256, glm::vec3(0.0, 1.0, 0.0));
	m.specularHighlight = 128;
	Cylinder cylindre(&m, 0.5f, 1.0f);
	Sphere sphere(&m, 1.0f, 16, 32);
	cylindre.rotate(PI/2, glm::vec3(1.0, 0.0, 0.0));
	cylindre.draw(this);
	eglSwapBuffers(m_disp, m_surface);
	return true;
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::deleteSurface()
{
	eglReleaseThread();
	eglMakeCurrent(m_disp, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	if(m_surface != EGL_NO_SURFACE)
		eglDestroySurface(m_disp, m_surface);

	m_surface = EGL_NO_SURFACE;
}

bool Renderer::hasDisplay()
{
	return (m_disp != EGL_NO_DISPLAY);
}

Camera* Renderer::getCamera()
{
	return &m_camera;
}

Color Renderer::getAmbientColor()
{
	return Color::BLACK;
}
