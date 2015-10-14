#ifndef DEF_NATIVEEVENTMANAGER
#define DEF_NATIVEEVENTMANAGER

#include <jni.h>
#include "EventManager.h"
#include "Rectangle2.h"
#include "Rectangle3.h"

extern "C"
{
	JNIEXPORT void JNICALL Java_com_gaulois94_EventManager_getTouchCoordEventManager(JNIEnv* jenv, jclass jcls, jobject jobj);
	JNIEXPORT bool JNICALL Java_com_gaulois94_EventManager_touchInScreenEventManager(JNIEnv* jenv, jclass jcls, jfloatArray rect, int mode);
}

#endif
