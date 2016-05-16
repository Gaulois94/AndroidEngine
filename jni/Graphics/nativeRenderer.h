#ifndef NATIVE_RENDERER_INCLUDE
#define NATIVE_RENDERER_INCLUDE

#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

extern "C"
{
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Renderer_createRenderer(JNIEnv* jenv, jclass jcls, jlong parent);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_initSurfaceRenderer(JNIEnv* jenv, jobject jobj, jlong rendererPtr, jobject surface);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_initRenderer(JNIEnv* jenv, jobject jobj, jlong rendererPtr);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_destroySurfaceRenderer(JNIEnv* jenv, jobject jobj, jlong rendererPtr);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_destroyRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_clearRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_displayRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr);
	JNIEXPORT bool JNICALL Java_com_gaulois94_Graphics_Renderer_hasDisplayRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr);

	//Event Function
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_onDownTouchRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr, jint pID, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_onUpTouchRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr, jint pID, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_onMoveTouchRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr, jint pID, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Renderer_accelerometerRenderer(JNIEnv* jenv, jobject obj, jlong rendererPtr, jfloat x, jfloat y, jfloat z);
};

#endif
