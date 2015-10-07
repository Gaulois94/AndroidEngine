#include "nativeRenderer.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Renderer_createRenderer(JNIEnv* jenv, jclass cls, jobject surface)
{
	Renderer* renderer = new Renderer();
	ANativeWindow* window = ANativeWindow_fromSurface(jenv, surface);
	renderer->initializeContext(window);

	renderer->setJobject(jobject);
	return (jlong)renderer;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_initRenderer(JNIEnv* jenv, jobject jobj, jlong rendererPtr, jobject surface)
{
	if(rendererPtr == 0)
		return;
	Renderer* renderer = (Renderer*) rendererPtr;
	ANativeWindow* window = ANativeWindow_fromSurface(jenv, surface);
	renderer->initializeSurface(window);
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
	if(rendererPtr == 0)
		return;
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

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_onDownTouchRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr, jfloat x, jfloat y)
{
	Renderer* renderer = (Renderer*)rendererPtr;
	renderer->onDownTouch(x, y);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_onUpTouchRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr, jfloat x, jfloat y)
{
	Renderer* renderer = (Renderer*)rendererPtr;
	renderer->onUpTouch(x, y);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_onMoveTouchRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr, jfloat x, jfloat y)
{
	Renderer* renderer = (Renderer*)rendererPtr;
	renderer->onMoveTouch(x, y);
}
