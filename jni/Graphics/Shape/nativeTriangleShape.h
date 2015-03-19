#ifndef NATIVETRIANGLESHAPE_INCLUDE
#define NATIVETRIANGLESHAPE_INCLUDE

#define GLM_FORCE_RADIANS

#include <jni.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Color.h"
#include "Shape/TriangleShape.h"

extern "C" {
	JNIEXPORT jlong       JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_createTriangleShape(JNIEnv *, jclass, jlong, jfloatArray, jfloatArray, jint, jint);
	JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_setDatasTriangleShape(JNIEnv *, jobject, jlong, jfloatArray, jfloatArray, jint);
	JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_setVertexTriangleShape(JNIEnv *, jobject, jlong, jfloatArray);
	JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_getPositionVertexTriangleShape(JNIEnv *, jobject, jlong, jint);
}
#endif
