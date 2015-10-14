#ifndef NATIVE_FONT_INCLUDE
#define NATIVE_FONT_INCLUDE

#include <jni.h>

#include "nativeTexture.h"
#include "Texture.h"
#include "Font.h"
#include "logger.h"

extern "C"
{
	JNIEXPORT jlong     JNICALL Java_com_gaulois94_Graphics_Font_loadFromFileFont(JNIEnv* jenv, jclass jcls, jobject bmp, jintArray width, jintArray height, jintArray posX, jintArray posY, int maxWidth, int maxHeight, int padX, int padY, jobject fontMetrics);

	JNIEXPORT jfloat    JNICALL Java_com_gaulois94_Graphics_Font_getLineHeightFont(JNIEnv* jenv, jobject jobj, jlong ptr);
	JNIEXPORT jintArray JNICALL Java_com_gaulois94_Graphics_Font_getPosFont(JNIEnv* jenv, jobject jobj, jlong ptr, jchar character);
	JNIEXPORT jintArray JNICALL Java_com_gaulois94_Graphics_Font_getSizeFont(JNIEnv* jenv, jobject jobj, jlong ptr, jchar character);
	JNIEXPORT jint      JNICALL Java_com_gaulois94_Graphics_Font_getLeadingFont(JNIEnv* jenv, jobject jobj, jlong ptr);
	JNIEXPORT jobject   JNICALL Java_com_gaulois94_Graphics_Font_getTextureFont(JNIEnv* jenv, jobject jobj, jlong ptr);
};

#endif

