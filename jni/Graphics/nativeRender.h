#ifndef DEF_NATIVERENDER_INCLUDE
#define DEF_NATIVERENDER_INCLUDE

#define GLM_FORCE_RADIANS

#include "Vector2.h"
#include "Rectangle3.h"
#include "Render.h"

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_gaulois_Graphics_Render_drawRender(JNIEnv* jenv, jobject render, jlong ptr, jlong drawable, jfloatArray transformation);
	JNIEXPORT void JNICALL Java_com_gaulois_Graphics_Render_displayRender(JNIEnv* jenv, jobject render, jlong ptr);
	JNIEXPORT void JNICALL Java_com_gaulois_Graphics_Render_initRender(JNIEnv* jenv, jobject render, jlong ptr);
	JNIEXPORT void JNICALL Java_com_gaulois_Graphics_Render_stopRender(JNIEnv* jenv, jobject render, jlong ptr);
	JNIEXPORT void JNICALL Java_com_gaulois_Graphics_Render_clearRender(JNIEnv* jenv, jobject render, jlong ptr);

	JNIEXPORT jfloatArray JNICALL Java_com_gaulois_Graphics_Render_getAmbientColorRender(JNIEnv* jenv, jobject render, jlong ptr);
	JNIEXPORT jobject JNICALL Java_com_gaulois_Graphics_Render_getCameraRender(JNIEnv* jenv, jobject render, jlong ptr);
	JNIEXPORT jfloatArray JNICALL Java_com_gaulois_Graphics_Render_getRectOnScreenRender(JNIEnv* jenv, jobject render, jlong ptr, jlong transformable);
	JNIEXPORT jfloatArray JNICALL Java_com_gaulois_Graphics_Render_getPositionOnScreenRender(JNIEnv* jenv, jobject render, jlong ptr, jfloatArray pos);
}


#endif
