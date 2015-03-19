#include <jni.h>
#include "Sprite.h"
#include "Rectangle2.h"

#ifndef _Included_com_gaulois94_Graphics_Sprite
#define _Included_com_gaulois94_Graphics_Sprite

#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Sprite_createSprite(JNIEnv *, jclass, jlong, jlong);
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Sprite_getTextureSprite(JNIEnv *, jobject, jlong);
	JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Sprite_getSubTextureRectSprite(JNIEnv *, jobject, jlong);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Sprite_setTextureSprite(JNIEnv *, jobject, jlong, jlong, jint);
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Sprite_setSubTextureRectSprite(JNIEnv *, jobject, jlong, jfloatArray);
#ifdef __cplusplus
}
#endif
#endif
