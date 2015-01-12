#ifndef NATIVE_BITMAP_INCLUDE
#define NATIVE_BITMAP_INCLUDE

#include <android/bitmap.h>
#include <jni.h>

#include "Bitmap.h"
#include "logger.h"

extern "C"
{
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Bitmap_createBitmap(JNIEnv* jenv, jclass jcls, jobject bmp);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Bitmap_invertPixelsBitmap(JNIEnv* jenv, jobject jobj, jlong ptr);
};

#endif
