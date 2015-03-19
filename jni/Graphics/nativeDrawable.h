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
JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_cleanShaders(JNIEnv *, jclass);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_getNumberOfShaders(JNIEnv *, jclass);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_existShaderFromKeyDrawable(JNIEnv *, jclass, jstring);

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_drawDrawable(JNIEnv *, jobject, jlong, jlong);
JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_setCanDrawDrawable(JNIEnv *, jobject, jlong, bool);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_canDrawDrawable(JNIEnv *, jobject, jlong);


JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_staticToCameraDrawable(JNIEnv *, jclass, jlong, jint);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_isStaticToCameraDrawable(JNIEnv *, jclass, jlong);

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_setMaterialDrawable(JNIEnv *, jclass, jlong, jlong);
JNIEXPORT jlong   JNICALL Java_com_gaulois94_Graphics_Drawable_getMaterialDrawable(JNIEnv *, jclass, jlong);

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_loadShadersDrawable(JNIEnv *, jclass, jobject);
#ifdef __cplusplus
}
#endif
#endif
