#ifndef BITMAP_INCLUDE
#define BITMAP_INCLUDE

#include <android/bitmap.h>
#include <jni.h>

#include "Bitmap.h"

extern "C"
{
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Bitmap_createBitmap(JNIEnv* jenv, jobject jobj, jobject bmp);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Bitmap_destroyBitmap(JNIEnv* jenv, jobject jobj, jlong ptr);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Bitmap_invertPixelsBitmap(JNIEnv* jenv, jobject jobj, jlong ptr);
};

#endif
