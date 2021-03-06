#include "nativeEventManager.h"

JNIEXPORT void JNICALL Java_com_gaulois94_EventManager_getTouchCoordEventManager(JNIEnv* jenv, jclass jcls, jint pID, jobject jobj)
{
	jclass tcClass    = jenv->GetObjectClass(jobj);
	jfieldID xID      = jenv->GetFieldID(tcClass, "x", "F");
	jfieldID yID      = jenv->GetFieldID(tcClass, "y", "F");
	jfieldID startXID = jenv->GetFieldID(tcClass, "startX", "F");
	jfieldID startYID = jenv->GetFieldID(tcClass, "startY", "F");
	jfieldID typeID   = jenv->GetFieldID(tcClass, "type", "I");
	
	jenv->SetFloatField(jobj, xID, touchCoord[pID].x);
	jenv->SetFloatField(jobj, yID, touchCoord[pID].y);
	jenv->SetFloatField(jobj, startXID, touchCoord[pID].startX);
	jenv->SetFloatField(jobj, startYID, touchCoord[pID].startY);
	jenv->SetIntField(jobj, typeID, touchCoord[pID].type);
}

JNIEXPORT bool JNICALL Java_com_gaulois94_EventManager_touchInScreenEventManager(JNIEnv* jenv, jclass jcls, jint pID, jfloatArray rect, int mode)
{
	jfloat* r = jenv->GetFloatArrayElements(rect, 0);
	//Rectangle2f
	if(mode==2)
		return touchInRect(Rectangle2f(r[0], r[1], r[2], r[3]), pID);

	//Rectangle3f
	else if (mode==3)
		return touchInRect(Rectangle3f(r[0], r[1], r[2], r[3], r[4], r[5]), pID);

	jenv->ReleaseFloatArrayElements(rect, r, 0);
	return false;
}
