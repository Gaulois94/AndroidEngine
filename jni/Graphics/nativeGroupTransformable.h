#ifndef  NATIVEGROUPTRANSFORMABLE_INC
#define  NATIVEGROUPTRANSFORMABLE_INC

#include <jni.h>
#include "Animation.h"

extern "C"
{
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_GroupTransformable_createGroupTransformable(JNIEnv jenv, jobject jobj, jfloatArray rect);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_GroupTransformable_addTransformableGroupTransformable(JNIEnv* jenv, jobject jobj, long ptr, long transformablePtr);
	JNIEXPORT bool JNICALL Java_com_gaulois94_Graphics_GroupTransformable_setEnableTransformationGroupTransformation(JNIEnv* jenv, jobject jobj, long ptr, bool e);
	JNIEXPORT bool JNICALL Java_com_gaulois94_Graphics_GroupTransformable_getEnableTransformationGroupTransformation(JNIEnv* jenv, jobject jobj, long ptr);
}


#endif   /* ----- #ifndef NATIVEGROUPTRANSFORMABLE_INC  ----- */
