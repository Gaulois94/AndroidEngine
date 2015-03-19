#ifndef NATIVE_UNICOLORMATERIAL_INCLUDE
#define NATIVE_UNICOLORMATERIAL_INCLUDE

#include "Materials/UniColorMaterial.h"
#include <jni.h>

extern "C" {
	JNIEXPORT jlong        JNICALL Java_com_gaulois94_Graphics_Materials_UniColorMaterial_createUniColorMaterial(JNIEnv *, jclass, jfloatArray);
	JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Materials_UniColorMaterial_setColorUniColorMaterial(JNIEnv *, jobject, jlong, jfloatArray);
	JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Materials_UniColorMaterial_getColorUniColorMaterial(JNIEnv *, jobject, jlong);
}
#endif

