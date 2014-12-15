#ifndef BITMAP_INCLUDE
#define BITMAP_INCLUDE

#include <jni.h>
#include "Texture.h"
#include "Bitmap.h"

extern "C"
{
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_initTexture(JNIEnv* jenv, jobject jobj, jlong width, jlong height);
	JNIEXPORT void  JNICALL Java_com_gaulois94_Graphics_Texture_destroyTexture(JNIEnv* jenv, jobject jobj, jlong texture);

	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_loadFromPixelsTexture(JNIEnv* jenv, jobject jobj, jFloatArray pixels, jlong width, jlong height, jbool alpha);
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_loadFromBitmapTexture(JNIEnv* jenv, jobject jobj, jlong bmp);

	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getIDTexture(JNIEnv* jenv, jobject jobj, jlong texture);
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getWidthTexture(JNIEnv* jenv, jobject jobj, jlong texture);
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getHeightTexture(JNIEnv* jenv, jobject jobj, jlong texture);
};

#endif

