#include "nativeGroupTransformable.h"

JNIEXPORT jlong Java_com_gaulois94_Graphics_GroupTransformable_createGroupTransformable(JNIEnv* jenv, jobject jobj, jfloatArray rect)
{
	jfloat* r = jenv->GetFloatArrayElements(r, 0);
	GroupTransformable* t = new GroupTransformable(Rectangle3f(r));
	jenv->ReleaseFloatArrayElements(rect, r, 0);
	return t;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_GroupTransformable_addTransformableGroupTransformable(JNIEnv* jenv, jobject jobj, long ptr, long transformablePtr)
{
	GroupTransformable* t = (GroupTransformable*)ptr;
	t->addTransformable((Transformable*)transformablePtr);
}

JNIEXPORT bool JNICALL Java_com_gaulois94_Graphics_GroupTransformable_setEnableTransformationGroupTransformation(JNIEnv* jenv, jobject jobj, long ptr, bool e)
{
	GroupTransformable* t = (GroupTransformable*)ptr;
	t->setEnableTransformation(e);
}

JNIEXPORT bool JNICALL Java_com_gaulois94_Graphics_GroupTransformable_getEnableTransformationGroupTransformation(JNIEnv* jenv, jobject jobj, long ptr)
{
	GroupTransformable* t = (GroupTransformable*)ptr;
	return t->getEnableTransformation();
}
