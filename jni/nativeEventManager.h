#ifndef DEF_EVENTMANAGER
#define DEF_EVENTMANAGER

#include <jni.h>
#include "EventManager.h"

extern "C"
{
	JNIEXPORT jobj JNICALL Java_com_gaulois94_EventManager_getTouchCoordEventManager(JNIEnv* jenv, jclass jcls, jobject jobj);
	JNIEXPORT bool        JNICALL Java_com_gaulois94_EventManager_touchInScreenEventManager(JNIEnv* jenv, jclass jcls, jfloatArray rect, int mode);
}

#endif
