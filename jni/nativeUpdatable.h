#ifndef DEF_NATIVEUPDATBLE_INCLUDE
#define DEF_NATIVEUPDATBLE_INCLUDE

#include <jni.h>
#include "Updatable.h"
#include "Render.h"

extern "C"
{
	JNIEXPORT jlong   JNICALL Java_com_gaulois94_Updatable_createUpdatable(JNIEnv* jenv, jclass jcls, jlong parent);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_updateFocusUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong renderer);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_onFocusUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong renderer);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_updateUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong render);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_onUpdateUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong render);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_addChildUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong child, int pos);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_setParentUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong parent, int pos);
	JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_removeChildUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong child);
	JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_removeChildPosUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, int pos);
	JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_isChildUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong child);
	JNIEXPORT jobject JNICALL Java_com_gaulois94_Updatable_getParentUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr);
}

#endif
