#include "nativeUpdatable.h"

JNIEXPORT jlong   JNICALL Java_com_gaulois94_Updatable_createUpdatable(JNIEnv* jenv, jclass jcls, jlong parent)
{
	return (jlong)(new Updatable(parent));
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_updateFocusUpdatable(JNIEnv* jenv, jlong ptr, jlong renderer)
{
	Updatable* u = (Updatable*)ptr;
	u->updateFocus((Renderer*)renderer);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_onFocusUpdatable(JNIEnv* jenv, jlong ptr, jlong renderer)
{
	Updatable* u = (Updatable*)ptr;
	u->onFocus((Renderer*)renderer);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_updateUpdatable(JNIEnv* jenv, jlong ptr, jlong render)
{
	Updatable* u = (Updatable*)ptr;
	u->update((Render*)render);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_onUpdateUpdatable(JNIEnv* jenv, jlong ptr, jlong render)
{
	Updatable* u = (Updatable*)ptr;
	u->onUpdate((Render*)render);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_addChildUpdatable(JNIEnv* jenv, jlong ptr, jlong child, int pos)
{
	Updatable* u = (Updatable*)ptr;
	u->addChild((Updatable*)child, pos);
}

JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_setParentUpdatable(JNIEnv* jenv, jlong ptr, jlong parent, int pos)
{
	Updatable* u = (Updatable*)ptr;
	u->setParent((Updatable*)parent, pos);
}

JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_removeChildUpdatable(JNIEnv* jenv, jlong ptr, jlong child)
{
	Updatable* u = (Updatable*)ptr;
	return u->removeChild((Updatable*)child);
}

JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_removeChildUpdatable(JNIEnv* jenv, jlong ptr, int pos)
{
	Updatable* u = (Updatable*)ptr;
	return u->removeChild(pos);
}

JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_isChildUpdatable(JNIEnv* jenv, jlong ptr, jlong child)
{
	Updatable* u = (Updatable*)ptr;
	return u->isChild(child);
}

JNIEXPORT jobject JNICALL Java_com_gaulois94_Updatable_getParentUpdatable(JNIEnv* jenv, jlong ptr)
{
	Updatable* u = (Updatable*)ptr;
	return u->getParent()->getJobject();
}
