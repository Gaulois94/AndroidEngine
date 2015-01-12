#ifndef NATIVE_TEXTURE_INCLUDE
#define NATIVE_TEXTURE_INCLUDE

#include <jni.h>
#include "Texture.h"
#include "Bitmap.h"
#include "nativeBitmap.h"

extern "C"
{
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_initTexture(JNIEnv* jenv, jclass jcls, jlong width, jlong height);

	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_loadFromPixelsTexture(JNIEnv* jenv, jclass jcls, jbyteArray pixels, jlong width, jlong height, jboolean alpha);
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_loadFromBitmapTexture(JNIEnv* jenv, jclass jcls, jlong bmp);
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_loadFromFileTexture(JNIEnv* jenv, jclass jcls, jstring path);

	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getIDTexture(JNIEnv* jenv, jobject jobj, jlong texture);
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getWidthTexture(JNIEnv* jenv, jobject jobj, jlong texture);
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getHeightTexture(JNIEnv* jenv, jobject jobj, jlong texture);
};

#endif
