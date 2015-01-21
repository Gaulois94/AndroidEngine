#include "nativeCircle.h"

JNIEXPORT jlong       JNICALL Java_com_gaulois94_Graphics_Shape_Circle_createCircle(JNIEnv *jenv, jclass jcls, jfloatArray colors, jint nbEdge)
{
	float* pc = jenv->GetFloatArrayElements(colors, 0);
	Circle* circle = new Circle(Color(pc[0], pc[1], pc[2], pc[3]), nbEdge);
	jenv->ReleaseFloatArrayElements(colors, pc, 0);

	return (long)circle;
}

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_Circle_setNbEdgeCircle(JNIEnv *jenv, jobject jobj, jlong ptr, jint nbEdge)
{
	Circle* circle = (Circle*) ptr;
	circle->setNbEdge(nbEdge);
}

JNIEXPORT int         JNICALL Java_com_gaulois94_Graphics_Shape_Circle_getNbEdgeCircle(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Circle* circle = (Circle*)ptr;
	return circle->getNbEdge();
}
