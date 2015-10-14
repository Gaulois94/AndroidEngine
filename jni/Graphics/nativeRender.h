#ifndef DEF_RENDER_INCLUDE
#define DEF_RENDER_INCLUDE

extern "C"
{
	JNIEXPORT jlong JNICALL Java_com_gaulois_Graphics_Render_createRender(JNIEnv* jenv, jobject render);
	JNIEXPORT void JNICALL Java_com_gaulois_Graphics_Render_drawRender(JNIEnv* jenv, jobject render, jlong drawable, jfloatArray transformation);
	JNIEXPORT jfloatArray JNICALL Java_com_gaulois_Graphics_Render_getAmbientColorRender(JNIEnv* jenv, jobject render);
	JNIEXPORT jobject JNICALL Java_com_gaulois_Graphics_Render_getCameraRender(JNIEnv* jenv, jobject render);
	JNIEXPORT jfloatArray JNICALL Java_com_gaulois_Graphics_Render_getRectOnScreenRender(JNIEnv* jenv, jobject render);
	JNIEXPORT jfloatArray JNICALL Java_com_gaulois_Graphics_Render_getPositionOnScreenRender(JNIEnv* jenv, jobject render);
}


#endif
