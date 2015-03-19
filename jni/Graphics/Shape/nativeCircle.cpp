#include "nativeCircle.h"

JNIEXPORT jlong       JNICALL Java_com_gaulois94_Graphics_Shape_Circle_createCircle(JNIEnv *jenv, jclass jcls, jlong material, jfloat radius, jint nbEdge)
{
	Circle* circle = new Circle((Material*)material, radius, nbEdge);

	return (long)circle;
}

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_Circle_setNbEdgeCircle(JNIEnv *jenv, jobject jobj, jlong ptr, jint nbEdge)
{
	Circle* circle = (Circle*) ptr;
	circle->setNbEdge(nbEdge);
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Shape_Circle_getCenterCircle(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Circle* circle   = (Circle*)ptr;
	glm::vec3 center = circle->getCenter();

	jfloatArray result = jenv->NewFloatArray(3);
	jenv->SetFloatArrayRegion(result, 0, 3, glm::value_ptr(center));

	return result;
}

JNIEXPORT int         JNICALL Java_com_gaulois94_Graphics_Shape_Circle_getNbEdgeCircle(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Circle* circle = (Circle*)ptr;
	return circle->getNbEdge();
}
