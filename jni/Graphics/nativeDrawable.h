#ifndef DEF_NATIVE_DRAWABLE_INCLUDE
#define DEF_NATIVE_DRAWABLE_INCLUDE

#include <jni.h>
#include "Drawable.h"
#include "File.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_addShaderDrawable(JNIEnv *, jclass, jlong);
JNIEXPORT jlong   JNICALL Java_com_gaulois94_Graphics_Drawable_getShaderDrawable(JNIEnv *, jclass, jstring);
JNIEXPORT jstring JNICALL Java_com_gaulois94_Graphics_Drawable_getKeyShaderDrawable(JNIEnv *, jclass, jlong);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_removeShaderFromKeyDrawable(JNIEnv *, jclass, jstring);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_removeShaderFromShaderDrawable(JNIEnv *, jclass, jlong);
JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_cleanShadersDrawable(JNIEnv *, jclass);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_getNumberOfShadersDrawable(JNIEnv *, jclass);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_existShaderFromKeyDrawable(JNIEnv *, jclass, jstring);

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_drawDrawable(JNIEnv *, jobject, jlong, jlong);
JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Drawable_canDrawDrawable(JNIEnv *, jobject, jlong);

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_loadShadersDrawable(JNIEnv *, jclass, jobject);
#ifdef __cplusplus
}
#endif
#endif
