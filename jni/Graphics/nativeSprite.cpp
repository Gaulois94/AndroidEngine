#include "nativeSprite.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Sprite_createSprite(JNIEnv *jenv, jclass jcls, jlong parent, jlong material, jlong texturePtr)
{
	Sprite* sprite = new Sprite((Updatable*)parent, (Material*)material, (Texture*)texturePtr);
	sprite->setJobject(jobject);
	return (long)sprite;
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Sprite_getTextureSprite(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Sprite* sprite = (Sprite*)ptr;
	return (long)(sprite->getTexture());
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Sprite_getSubTextureRectSprite(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Sprite* sprite       = (Sprite*)ptr;
	FloatRect2 floatRect = sprite->getSubTextureRect();

	float rect[4]        = {floatRect.x, floatRect.y, floatRect.width, floatRect.height};
	jfloatArray result   = jenv->NewFloatArray(4);

	jenv->SetFloatArrayRegion(result, 0, 4, rect);
	return result;	
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Sprite_setTextureSprite(JNIEnv *jenv, jobject jobj, jlong ptr, jlong texturePtr, jint resetSubRect)
{
	Texture* texture = (Texture*)texturePtr;
	Sprite* sprite   = (Sprite*)ptr;

	sprite->setTexture(texture, resetSubRect);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Sprite_setSubTextureRectSprite(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray rect)
{
	float* r        = jenv->GetFloatArrayElements(rect, 0);
	FloatRect2 rect2(r[0], r[1], r[2], r[3]);
	Sprite* sprite  = (Sprite*)ptr;
	sprite->setSubTextureRect(rect2);
	jenv->ReleaseFloatArrayElements(rect, r, 0);
}
