#ifndef NATIVE_JNIMADEOF_INCLUDE
#define NATIVE_JNIMADEOF_INCLUDE

#include <jni.h>
#include "JniMadeOf.h"

extern "C"
{
	JNIEXPORT void JNICALL Java_com_gaulois94_JniMadeOf_destroyJniMadeOf(JNIEnv* jenv, jobject jobj, jlong ptr);
};

#endif
