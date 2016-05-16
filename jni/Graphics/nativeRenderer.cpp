#include "nativeRenderer.h"
#include "Renderer.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Renderer_createRenderer(JNIEnv* jenv, jclass jcls, jlong parent)
{
	JniMadeOf::jenv = jenv;
	Renderer* renderer = new Renderer((Updatable*)parent);

	return (jlong)renderer;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_initSurfaceRenderer(JNIEnv* jenv, jobject jobj, jlong rendererPtr, jobject surface)
{
	if(rendererPtr == 0)
		return;
	Renderer* renderer = (Renderer*) rendererPtr;
	renderer->releaseSurface();
	ANativeWindow* window = ANativeWindow_fromSurface(jenv, surface);
	renderer->initializeSurface(window);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_initRenderer(JNIEnv* jenv, jobject jobj, jlong rendererPtr)
{
	Renderer* renderer = (Renderer*) rendererPtr;
	renderer->init();
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_destroyRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr)
{
	Renderer* renderer = (Renderer*) rendererPtr;
	if(renderer)
		delete renderer;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_destroySurfaceRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr)
{
	if(rendererPtr == 0)
		return;
	Renderer* renderer = (Renderer*) rendererPtr;
	renderer->deleteSurface();
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_clearRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr)
{
	Renderer* renderer = (Renderer*) rendererPtr;
	renderer->clear();
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_displayRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr)
{
	if(rendererPtr == 0)
		return;
	Renderer* renderer = (Renderer*) rendererPtr;
	renderer->display();
}

JNIEXPORT bool JNICALL Java_com_gaulois94_Graphics_Renderer_hasDisplayRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr)
{
	if(rendererPtr == 0)
		return false;
	Renderer* renderer = (Renderer*) rendererPtr;
	return renderer->hasDisplay();
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_onDownTouchRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr, jint pID, jfloat x, jfloat y)
{
	Renderer* renderer = (Renderer*)rendererPtr;
	renderer->onDownTouchEvent(pID, x, y);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_onUpTouchRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr, jint pID, jfloat x, jfloat y)
{
	Renderer* renderer = (Renderer*)rendererPtr;
	renderer->onUpTouchEvent(pID, x, y);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_onMoveTouchRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr, jint pID, jfloat x, jfloat y)
{
	Renderer* renderer = (Renderer*)rendererPtr;
	renderer->onMoveTouchEvent(pID, x, y);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_accelerometerRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr, jfloat x, jfloat y, jfloat z)
{
	Renderer* renderer = (Renderer*)rendererPtr;
	renderer->accelerometerEvent(x, y, z);
}
