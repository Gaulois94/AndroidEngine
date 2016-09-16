#include "Renderer.h"
#include "Graphics/Materials/UniColorMaterial.h"
#include "Graphics/Materials/TextureMaterial.h"
#include "Graphics/Text.h"
#include "Graphics/Font.h"
#include "Graphics/Sprite.h"
#include "Graphics/Widgets/Menu.h"

Renderer::Renderer(Updatable* parent) : Render(parent), m_disp(EGL_NO_DISPLAY), m_surface(EGL_NO_SURFACE), m_context(EGL_NO_CONTEXT),
										m_conf(0), m_nbConf(0), m_format(0), m_width(0), m_window(0)
{
	initializeContext();
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::updateFocus(uint32_t pID)
{
	Updatable::updateFocus(pID, *this);
	if(focusIsCheck == false)
		onFocus(pID, *this);
	Updatable::focusIsCheck = false;
}

void Renderer::update(Render& render)
{
	Updatable::update(render);
	Updatable::updateGPU(render);
}

void Renderer::initDraw()
{
    if(!eglMakeCurrent(m_disp, m_surface, m_surface, m_context))
	{
		LOG_ERROR("Init Draw Can't make this context the current one. Error : %d", eglGetError());
		return;
	}
	
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

	updateFocus(i);
}

void Renderer::accelerometerEvent(float x, float y, float z)
{
}

bool Renderer::keyUpEvent(int32_t keyCode)
{
	LOG_ERROR("KEY UP CODE : %d", keyCode);
	Updatable::keyUp(keyCode);
	if(!Updatable::keyUpIsCheck)
		return onKeyUp(keyCode);
	else
	{
		Updatable::keyUpIsCheck = false;
		return true;
	}
}

bool Renderer::keyDownEvent(int32_t keyCode)
{
	LOG_ERROR("KEY DOWN CODE : %d", keyCode);
	Updatable::keyDown(keyCode);
	if(!Updatable::keyDownIsCheck)
		return onKeyDown(keyCode);
	else
	{
		Updatable::keyDownIsCheck = false;
		return true;
	}
}

void Renderer::onUpTouchEvent(uint32_t i, float x, float y)
{
	touchCoord[i].type = UP;
	touchCoord[i].x    = x;
	touchCoord[i].y    = y;
}

void Renderer::onMoveTouchEvent(uint32_t i, float x, float y)
{
	touchCoord[i].x    = x;
	touchCoord[i].y    = y;
	touchCoord[i].type = MOVE;
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
	//Get the InputMethodManager
	//
	//InputMethodManager imm = (InputMethodManager) mContext.getSystemService(Context.INPUT_METHOD_SERVICE);
	JNIEnv* env                       = JniMadeOf::getJEnv();
	jclass immClass                 = env->FindClass("android/view/inputmethod/InputMethodManager");
	jclass ctxClass                 = env->FindClass("android/content/Context");
	jmethodID getSystemService      = env->GetMethodID(ctxClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
	jfieldID INPUT_METHOD_SERVICEID = env->GetStaticFieldID(ctxClass, "INPUT_METHOD_SERVICE", "Ljava/lang/String;");
	jobject INPUT_METHOD_SERVICE    = env->GetStaticObjectField(ctxClass, INPUT_METHOD_SERVICEID);
	jobject imm                     = env->CallObjectMethod(JniMadeOf::context, getSystemService, INPUT_METHOD_SERVICE);

	//Call the correct function following show value
	//imm.toggleSoftInput(InputMethodManager.SHOW_FORCED,0);
	//imm.toggleSoftInput(InputMethodManager.HIDE_IMPLICIT_ONLY,0);
	jmethodID toggleSoftInputID     = env->GetMethodID(immClass, "toggleSoftInput", "(II)V");
	jfieldID SHOWID                 = env->GetStaticFieldID(immClass, (show) ? "SHOW_FORCED" : "HIDE_IMPLICIT_ONLY", "I");
	int SHOW                        = env->GetStaticIntField(immClass, SHOWID);
	env->CallVoidMethod(imm, toggleSoftInputID, SHOW, 0);
}
