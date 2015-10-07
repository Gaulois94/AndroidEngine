#include "nativeJniMadeOf.h"

JNIEXPORT void JNICALL Java_com_gaulois94_JniMadeOf_destroyJniMadeOf(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	JniMadeOf* obj = (JniMadeOf*) ptr;
	delete obj;
}

JNIEXPORT void JNICALL Java_com_gaulois94_JniMadeOf_setJNIEnvJniMadeOf(JNIEnv* jenv, jclass jcls)
{
	JniMadeOf::jenv = jenv;
}
