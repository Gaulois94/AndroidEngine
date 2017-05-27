#include "Renderer.h"
#include "Graphics/Materials/UniColorMaterial.h"
#include "Graphics/Materials/TextureMaterial.h"
#include "Graphics/Text.h"
#include "Graphics/Font.h"
#include "Graphics/Sprite.h"
#include "Graphics/Widgets/Menu.h"
#include "globalValues.h"
#include "time.h"

uint64_t currentTime=0;

Renderer* globalRenderer = NULL;

Renderer::Renderer(Updatable* parent) : Render(parent), m_disp(EGL_NO_DISPLAY), m_surface(EGL_NO_SURFACE), m_context(EGL_NO_CONTEXT),
										m_conf(0), m_nbConf(0), m_format(0), m_width(0), m_window(0)
{
	initializeContext();
	globalRenderer = this;
}

Renderer::~Renderer()
{
	terminate();
}

void Renderer::terminate()
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

bool Renderer::initializeContext()
{
	m_start = false;
	terminate();

	//Initialize the egl context
	const EGLint attribs[] = 
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
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

	if(!(m_context = eglCreateContext(m_disp, m_conf, EGL_NO_CONTEXT, eglAttribs)))
	{
		LOG_ERROR("Can't create an EGL context. Error : %d", eglGetError());
		return false;
	}

	if(!eglMakeCurrent(m_disp, EGL_NO_SURFACE, EGL_NO_SURFACE, m_context))
	{
		LOG_ERROR("Can't bind this context. Error : %d", eglGetError());
		return false;
	}

	//Initialize OpenGL
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	Drawable::initShaders();

	return true;
}

void Renderer::releaseSurface()
{
	if(m_window)
	{
		ANativeWindow_release(m_window);
		m_window = NULL;
	}
}

void Renderer::initializeSurface(ANativeWindow* window)
{
	if(window == NULL)
		return;

	deleteSurface();
	releaseSurface();
	m_window = window;
	m_start = false;

	ANativeWindow_setBuffersGeometry(window, 0, 0, m_format);

	if(!(m_surface = eglCreateWindowSurface(m_disp, m_conf, window, 0)))
	{
		LOG_ERROR("Can't create an EGL surface from this window. Error : %d", eglGetError());
		return;
	}

	if(!eglMakeCurrent(m_disp, m_surface, m_surface, m_context))
	{
		LOG_ERROR("Can't make this surface current. Error : %d", eglGetError());
		return;
	}

	eglQuerySurface(m_disp, m_surface, EGL_WIDTH, &m_width);
	eglQuerySurface(m_disp, m_surface, EGL_HEIGHT, &m_height);

	setViewport(m_width, m_height);
	m_start = true;
}

void Renderer::init()
{
}

void Renderer::display()
{
	eglSwapBuffers(m_disp, m_surface);
}

void Renderer::clear()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::updateFocus(const TouchEvent& te)
{
	Render::updateFocus(te, *this);
	Updatable::focusIsCheck = false;
}

void Renderer::update(Render& render)
{
	Event* ev;
	while(m_events.size() > 0)
	{
		ev = m_events.front();
		switch(ev->type)
		{
			case TOUCH_DOWN:
				updateFocus(ev->touchEvent);
				break;

			case TOUCH_UP:
				if(Updatable::objectFocused)
					updateTouchUp(ev->touchEvent, *this);
				break;

			case KEYDOWN:
				keyDown(ev->keyEvent.keyCode);
				Updatable::keyDownIsCheck = false;
				break;

			case KEYUP:
				keyUp(ev->keyEvent.keyCode);
				Updatable::keyUpIsCheck = false;
				break;	

			case TOUCH_MOVE:
				moveEvent(ev->touchEvent, *this);
				break;

			default:
				break;
		}

		m_events.pop_front();
		delete ev;
	}

	Render::update(render);
	Render::updateGPU(render);

	struct timespec t;
	clock_gettime(CLOCK_REALTIME, &t);

	LOG_ERROR("FPS %f", 1.0e9/(t.tv_nsec - currentTime));
	currentTime = t.tv_nsec;
}

void Renderer::initDraw()
{
    if(!eglMakeCurrent(m_disp, m_surface, m_surface, m_context))
	{
		LOG_ERROR("Init Draw Can't make this context the current one. Error : %d", eglGetError());
		return;
	}
	
	glViewport(0, 0, m_width, m_height);
}

void Renderer::stopDraw()
{
	eglMakeCurrent(m_disp, EGL_NO_SURFACE, EGL_NO_SURFACE, m_context);
}

void Renderer::onDownTouchEvent(uint32_t i, float x, float y)
{
	touchCoord[i].type   = DOWN;
	touchCoord[i].startX = x;
	touchCoord[i].x      = x;
	touchCoord[i].startY = y;
	touchCoord[i].y      = y;

	Event* ev = new Event();
	ev->type = TOUCH_DOWN;
	ev->touchEvent.pid    = i;
	ev->touchEvent.x      = x;
	ev->touchEvent.y      = y;

	m_events.push_back(ev);
}

void Renderer::accelerometerEvent(float x, float y, float z)
{
}

bool Renderer::keyUpEvent(int32_t keyCode)
{
	Event* ev = new Event();
	ev->type = KEYUP;
	ev->keyEvent.keyCode = keyCode;
	m_events.push_back(ev);

	return true;
}

bool Renderer::keyDownEvent(int32_t keyCode)
{
	Event* ev = new Event();
	ev->type = KEYDOWN;
	ev->keyEvent.keyCode = keyCode;
	m_events.push_back(ev);

	return true;
}

void Renderer::onUpTouchEvent(uint32_t i, float x, float y)
{
	touchCoord[i].type = UP;
	touchCoord[i].x    = x;
	touchCoord[i].y    = y;

	Event* ev = new Event();
	ev->type = TOUCH_UP;
	ev->touchEvent.pid = i;
	ev->touchEvent.x   = x;
	ev->touchEvent.y   = y;

	m_events.push_back(ev);
}

void Renderer::onMoveTouchEvent(uint32_t i, float x, float y)
{
	touchCoord[i].x    = x;
	touchCoord[i].y    = y;
	touchCoord[i].type = MOVE;

	Event* ev = new Event();
	ev->type = TOUCH_MOVE;
	ev->touchEvent.pid = i;
	ev->touchEvent.x   = x;
	ev->touchEvent.y   = y;

	m_events.push_back(ev);
}

void Renderer::deleteSurface()
{
	if(m_surface != EGL_NO_SURFACE)
	{
		eglMakeCurrent(m_disp, EGL_NO_SURFACE, EGL_NO_SURFACE, m_context);
		eglDestroySurface(m_disp, m_surface);
		m_surface = EGL_NO_SURFACE;
		m_window = NULL;
	}
}

void Renderer::setViewport(int w, int h)
{
	m_width  = w;
	m_height = h;
	glViewport(0, 0, m_width, m_height);
}

bool Renderer::hasDisplay()
{
	return (m_disp != EGL_NO_DISPLAY);
}

void Renderer::showKeyboard(bool show)
{
	Keyboard::showKeyboard(show);
}
