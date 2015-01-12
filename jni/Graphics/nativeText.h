#include <jni.h>
#include "Text.h"

#ifndef DEF_INCLUDE_TEXT
#define DEF_INCLUDE_TEXT

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Text_createText(JNIEnv *, jclass, jlong, jstring, jfloatArray);
JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Text_setTextText(JNIEnv *, jobject, jlong, jstring);
JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Text_setColorText(JNIEnv *, jobject, jlong, jfloatArray);
JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Text_setFontText(JNIEnv *, jobject, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif
