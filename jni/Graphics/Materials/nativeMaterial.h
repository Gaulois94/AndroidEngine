#ifndef NATIVE_MATERIAL_INCLUDE
#define NATIVE_MATERIAL_INCLUDE

#include "Materials/Material.h"
#include "Renderer.h"
#include "Texture.h"
#include <jni.h>

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Materials_Material_enableShaderMaterial(JNIEnv *, jobject, jlong);
JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Materials_Material_bindTextureMaterial(JNIEnv *, jobject, jlong, jlong);

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Materials_Material_initMaterial(JNIEnv *, jobject, jlong, jlong);
JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Materials_Material_unbindTextureMaterial(JNIEnv *, jobject, jlong);
JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Materials_Material_disableShaderMaterial(JNIEnv *, jobject, jlong);
JNIEXPORT long JNICALL Java_com_gaulois94_Graphics_Materials_Material_getShaderMaterial(JNIEnv *, jobject, jlong);

#endif
