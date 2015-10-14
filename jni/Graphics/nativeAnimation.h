#ifndef DEF_NATIVEANIMATION
#define DEF_NATIVEANIMATION

#include <jni.h>
#include "Animation.h"

extern "C"
{
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Animation_setSubNSpriteCoordsAnimation(JNIEnv* jenv, jobject jobj, long ptr, int n);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Animation_setInAnimationAnimation(JNIEnv* jenv, jobject jobj, long ptr, bool inAnimation, int reset);
	JNIEXPORT bool JNICALL Java_com_gaulois94_Graphics_Animation_inAnimationAnimation(JNIEnv* jenv, jobject jobj, long ptr);
}

#endif
