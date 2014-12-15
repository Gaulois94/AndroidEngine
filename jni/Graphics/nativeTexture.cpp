#include "nativeTexture.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_initTexture(JNIEnv* jenv, jobject jobj, jlong width, jlong height)
{
	Texture* texture = new Texture(width, height);
	return texture;
}

JNIEXPORT void  JNICALL Java_com_gaulois94_Graphics_Texture_destroyTexture(JNIEnv* jenv, jobject jobj, jlong texture)
{
	Texture* ptr = (Texture*) texture;
	delete ptr;
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_loadFromPixelsTexture(JNIEnv* jenv, jobject jobj, jFloatArray pixels, jlong width, jlong height, jbool alpha)
{
	float* p = jenv->GetFloatArrayElements(pixels, 0);
	Texture* texture = new Texture(p, width, height, alpha);
	return texture;
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_loadFromBitmapTexture(JNIEnv* jenv, jobject jobj, jlong bmp)
{
	Texture* texture = new Texture((Bitmap*) bmp);
	return texture;
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getIDTexture(JNIEnv* jenv, jobject jobj, jlong texture)
{
	Texture* ptr = (Texture*) texture;
	return ptr->getID();
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getWidthTexture(JNIEnv* jenv, jobject jobj, jlong texture)
{
	Texture* ptr = (Texture*) texture;
	return ptr->getWidth();
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Texture_getHeightTexture(JNIEnv* jenv, jobject jobj, jlong texture)
{
	Texture* ptr = (Texture*) texture;
	return ptr->getHeight();
}
