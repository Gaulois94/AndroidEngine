#include "nativeRender.h"

JNIEXPORT void JNICALL Java_com_gaulois_Graphics_Render_drawRender(JNIEnv* jenv, jobject jobj, jlong ptr, jlong drawable, jfloatArray transformation)
{
	Render* render = (Render*)ptr;
	float* t = jenv->GetFloatArrayElements(transformation, 0);
	render->draw(*(Drawable*)drawable, glm::make_mat4(t));
	jenv->ReleaseFloatArrayElements(transformation, t, 0);
}

JNIEXPORT void JNICALL Java_com_gaulois_Graphics_Render_displayRender(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	((Render*)ptr)->display();
}

JNIEXPORT void JNICALL Java_com_gaulois_Graphics_Render_initDrawRender(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	((Render*)ptr)->initDraw();
}

JNIEXPORT void JNICALL Java_com_gaulois_Graphics_Render_stopDrawRender(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	((Render*)ptr)->stopDraw();
}

JNIEXPORT void JNICALL Java_com_gaulois_Graphics_Render_clearRender(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	((Render*)ptr)->clear();
}


JNIEXPORT jfloatArray JNICALL Java_com_gaulois_Graphics_Render_getAmbientColorRender(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	jfloatArray result = jenv->NewFloatArray(4);
	Color ambientColor = ((Render*)ptr)->getAmbientColor();
	float c[4] = {ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a};
	jenv->SetFloatArrayRegion(result, 0, 4, c);
	return result;
}

JNIEXPORT jobject JNICALL Java_com_gaulois_Graphics_Render_getCameraRender(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	return ((Render*)ptr)->getCamera().getJobject();
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois_Graphics_Render_getRectOnScreenRender(JNIEnv* jenv, jobject jobj, jlong ptr, jlong transformable)
{
	jfloatArray result = jenv->NewFloatArray(6);
/*  Rectangle3f rect = ((Render*)ptr)->getRectOnScreen(*(Transformable*)transformable);
	float c[6] = {rect.x, rect.y, rect.z, rect.width, rect.height, rect.depth};
	jenv->SetFloatArrayRegion(result, 0, 6, c);
*/
	return result;
	
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois_Graphics_Render_getPositionOnScreenRender(JNIEnv* jenv, jobject jobj, jlong ptr, jfloatArray pos)
{
	float* p = jenv->GetFloatArrayElements(pos, 0);
	jfloatArray result = jenv->NewFloatArray(4);
	glm::vec3 pV = ((Render*)ptr)->getPositionOnScreen(glm::vec3(p[0], p[1], p[2]));
	float pVF[3] = {pV[0], pV[1], pV[2]};
	jenv->SetFloatArrayRegion(result, 0, 4, pVF);
	jenv->ReleaseFloatArrayElements(pos, p, 0);
	return result;
}
