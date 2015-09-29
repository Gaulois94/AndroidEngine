#ifndef DEF_NATIVECAMERA_INCLUDE
#define DEF_NATIVECAMERA_INCLUDE

#include <jni.h>
#include "Camera.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Camera_createCamera(JNIEnv *, jclass);
JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Camera_getPositionCamera(JNIEnv *, jobject, jlong);
JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Camera_lookAtCamera(JNIEnv *, jobject, jlong, jfloatArray, jfloatArray);
JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Camera_setPositionCamera(JNIEnv *, jobject, jlong, jfloatArray);
JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Camera_setOrientationCamera(JNIEnv *, jobject, jlong, jfloatArray);

#ifdef __cplusplus
}
#endif
#endif
