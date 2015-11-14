#ifndef DEF_NATIVE_DRAWABLE_INCLUDE
#define DEF_NATIVE_DRAWABLE_INCLUDE

#include <jni.h>
#include <glm/gtc/type_ptr.hpp>
#include "Drawable.h"
#include "File.h"

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------Shader control------------------------------------------- */
JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_addShaderDrawable(JNIEnv *, jclass, jlong);
JNIEXPORT jlong   JNICALL Java_com_gaulois94_Graphics_Drawable_getShaderDrawable(JNIEnv *, jclass, jstring);
JNIEXPORT jstring JNICALL Java_com_gaulois94_Graphics_Drawable_getKeyShaderDrawable(JNIEnv *, jclass, jlong);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_removeShaderFromKeyDrawable(JNIEnv *, jclass, jstring);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_removeShaderFromShaderDrawable(JNIEnv *, jclass, jlong);
JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_cleanShaders(JNIEnv *, jclass);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_getNumberOfShaders(JNIEnv *, jclass);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_existShaderFromKeyDrawable(JNIEnv *, jclass, jstring);
/* ----------------------------------------End Shader control------------------------------------------- */

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_drawDrawable(JNIEnv *, jobject, jlong, jlong, jfloatArray);
JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_onDrawDrawable(JNIEnv *, jobject, jlong, jlong, jfloatArray);
JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_onMoveDrawable(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray move, bool useScale);
JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_onRotateDrawable(JNIEnv *jenv, jobject jobj, jlong ptr, jfloat angle, jfloatArray axis, jfloatArray origin);
JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_onScaleDrawable(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray);


JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_staticToCameraDrawable(JNIEnv *, jclass, jlong, jint);
JNIEXPORT jint    JNICALL Java_com_gaulois94_Graphics_Drawable_isStaticToCameraDrawable(JNIEnv *, jclass, jlong);

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_setMaterialDrawable(JNIEnv *, jclass, jlong, jlong);
JNIEXPORT jlong   JNICALL Java_com_gaulois94_Graphics_Drawable_getMaterialDrawable(JNIEnv *, jclass, jlong);

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_setTransToChildrenDrawable(JNIEnv *, jclass, jlong, bool);
JNIEXPORT bool   JNICALL Java_com_gaulois94_Graphics_Drawable_getTransToChildrenDrawable(JNIEnv *, jclass, jlong);

JNIEXPORT void    JNICALL Java_com_gaulois94_Graphics_Drawable_loadShadersDrawable(JNIEnv *, jclass, jobject);
#ifdef __cplusplus
}
#endif
#endif
