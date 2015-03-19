#ifndef NATIVE_UNICOLORMATERIAL_INCLUDE
#define NATIVE_UNICOLORMATERIAL_INCLUDE

#include "Materials/ColorMaterial.h"
#include <jni.h>

JNIEXPORT long        JNICALL Java_com_gaulois94_Graphics_Materials_ColorMaterial_createColorMaterial(JNIEnv *, jclass, jfloatArray, int nbVertex);
JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Materials_ColorMaterial_setColorColorMaterial(JNIEnv *, jobject, jlong, jfloatArray, int nbVertex);
JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Materials_ColorMaterial_getColorColorMaterial(JNIEnv *, jobject, jlong);
JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Materials_ColorMaterial_getColorColorMaterial(JNIEnv *, jobject, jlong, int);
JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Materials_ColorMaterial_getNbVertexColorMaterial(JNIEnv *jenv, jobject jobj, jlong ptr);

#endif

