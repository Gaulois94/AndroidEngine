#include "nativeUpdatable.h"

JNIEXPORT jlong   JNICALL Java_com_gaulois94_Updatable_createUpdatable(JNIEnv* jenv, jclass jcls, jlong parent)
{
	Updatable* u = new Updatable((Updatable*)parent);
	return (jlong)(u);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_updateFocusUpdatable(JNIEnv* jenv, jobject jobj, jint pID, jlong ptr, jlong renderer)
{
	Updatable* u = (Updatable*)ptr;
	u->updateFocus(pID, *(Render*)renderer);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_onFocusUpdatable(JNIEnv* jenv, jobject jobj, jint pID, jlong ptr, jlong renderer)
{
	Updatable* u = (Updatable*)ptr;
	u->onFocus(pID, *(Render*)renderer);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_updateUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong render)
{
	Updatable* u = (Updatable*)ptr;
	u->update(*(Render*)render);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_onUpdateUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong render)
{
	Updatable* u = (Updatable*)ptr;
	u->onUpdate(*(Render*)render);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_addChildUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong child, int pos)
{
	Updatable* u = (Updatable*)ptr;
	u->addChild((Updatable*)child, pos);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_setParentUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong parent, int pos)
{
	Updatable* u = (Updatable*)ptr;
	u->setParent((Updatable*)parent, pos);
}

JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_removeChildUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong child)
{
	Updatable* u = (Updatable*)ptr;
	return u->removeChild((Updatable*)child);
}

JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_removeChildPosUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, int pos)
{
	Updatable* u = (Updatable*)ptr;
	return u->removeChild(pos);
}

JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_isChildUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr, jlong child)
{
	Updatable* u = (Updatable*)ptr;
	return u->isChild((Updatable*)child);
}

JNIEXPORT jobject JNICALL Java_com_gaulois94_Updatable_getParentUpdatable(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	Updatable* u = (Updatable*)ptr;
	return u->getParent()->getJobject();
}
