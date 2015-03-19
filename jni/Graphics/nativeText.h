#ifndef DEF_INCLUDE_TEXT
#define DEF_INCLUDE_TEXT

#include <jni.h>
#include "Text.h"
#include "Materials/Material.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Text_createText(JNIEnv *, jclass, jint, jlong, jstring);
JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Text_setTextText(JNIEnv *, jobject, jlong, jstring);
JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Text_setFontText(JNIEnv *, jobject, jlong, jlong);

JNIEXPORT long JNICALL Java_com_gaulois94_Graphics_Text_getFontText(JNIEnv *, jobject, jlong);
JNIEXPORT jstring JNICALL Java_com_gaulois94_Graphics_Text_getTextText(JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
