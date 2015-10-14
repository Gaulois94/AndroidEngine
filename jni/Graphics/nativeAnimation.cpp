#include "nativeAnimation.h"

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Animation_setSubNSpriteCoordsAnimation(JNIEnv* jenv, jobject jobj, long ptr, int n)
{
	((Animation*)ptr)->setSubNSpriteCoords(n);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Animation_setInAnimationAnimation(JNIEnv* jenv, jobject jobj, long ptr, bool inAnimation, int reset)
{
	((Animation*)ptr)->setInAnimation(inAnimation, reset);
}

JNIEXPORT bool JNICALL Java_com_gaulois94_Graphics_Animation_inAnimationAnimation(JNIEnv* jenv, jobject jobj, long ptr)
{
	return ((Animation*)ptr)->inAnimation();
}
