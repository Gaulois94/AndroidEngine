#ifndef NATIVE_TRANSFORMABLE_INCLUDE
#define NATIVE_TRANSFORMABLE_INCLUDE

#define GLM_FORCE_RADIANS

#include <jni.h>
#include <glm/glm.hpp>

#include "Transformable.h"

extern "C"
{
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Transformable_createTransformable(JNIEnv* jenv, jclass jcls);

	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_moveTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, jfloatArray move);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_setPositionTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, jfloatArray position, jint useScale);

	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_rotateTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, float angle, jfloatArray rotate);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_setRotationTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, float angle, jfloatArray rotate);

	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_scaleTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, jfloatArray scale);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_setScaleTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, jfloatArray scale);

	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_setSphericCoordinateTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, float r, float theta, float phi);

	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_rotatePhiTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, float phi);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_rotateThetaTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, float theta);

	JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Transformable_getPositionTranformable(JNIEnv* jenv, jobject jobj, jlong transPtr, jint useScale);
	JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Transformable_getSphericCoordinateTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr);
	JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Transformable_getEulerRotationTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr);
};

#endif
