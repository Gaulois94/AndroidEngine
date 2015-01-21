#include "Shape/nativeTriangleShape.h"

JNIEXPORT jlong       JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_createTriangleShape(JNIEnv *jenv, jclass jcls, jfloatArray vertexCoords, jfloatArray colors, jint nbVertex, jint useUniColor, jint mode)
{
	float* pv = jenv->GetFloatArrayElements(vertexCoords, 0);
	float* pc = jenv->GetFloatArrayElements(colors, 0);

	TriangleShape* result = new TriangleShape(pv, nbVertex, pc, useUniColor, mode);
	jenv->ReleaseFloatArrayElements(vertexCoords, pv, 0);
	jenv->ReleaseFloatArrayElements(colors, pc, 0);

	return (long)result;
}

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_setVertexTriangleShape(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray vertexCoords, jfloatArray colors, jint nbVertex, jint useUniColor)
{
	TriangleShape* triangleShape = (TriangleShape*)	ptr;

	float* pv = jenv->GetFloatArrayElements(vertexCoords, 0);
	float* pc = jenv->GetFloatArrayElements(colors, 0);

	triangleShape->setDatas(pv, pc, nbVertex, useUniColor);
}

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_setVertexTriangleShape(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray vertexCoords)
{
	TriangleShape* triangleShape = (TriangleShape*) ptr;
	float* pv = jenv->GetFloatArrayElements(vertexCoords, 0);

	int nbVertex = triangleShape->getNbVertex();
	glm::vec3* v = (glm::vec3*)malloc(nbVertex * sizeof(glm::vec3));
	for(int i=0; i < nbVertex; i++)
	{
		v[i].x = pv[3*i + 0];
		v[i].y = pv[3*i + 1];
		v[i].z = pv[3*i + 2];
	}

	triangleShape->setVertexCoord(v);

	jenv->ReleaseFloatArrayElements(vertexCoords, pv, 0);
	free(v);
}

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_setColorsTriangleShape(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray colors)
{
	TriangleShape* triangleShape = (TriangleShape*) ptr;

	float* pc = jenv->GetFloatArrayElements(colors, 0);

	int nbVertex = triangleShape->getNbVertex();
	Color* c = (Color*)malloc(nbVertex * sizeof(Color));
	for(int i=0; i < nbVertex; i++)
	{
		c[i].r = pc[4*i + 0];
		c[i].g = pc[4*i + 1];
		c[i].b = pc[4*i + 2];
		c[i].a = pc[4*i + 3];
	}

	triangleShape->setColors(c);

	jenv->ReleaseFloatArrayElements(colors, pc, 0);
	free(c);
}

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_setUniColorTriangleShape(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray colors)
{
	TriangleShape* triangleShape = (TriangleShape*) ptr;

	float* pc = jenv->GetFloatArrayElements(colors, 0);
	Color c(pc[0], pc[1], pc[2], pc[3]);

	triangleShape->setUniColor(c);
	jenv->ReleaseFloatArrayElements(colors, pc, 0);
}

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_useUniColorTriangleShape(JNIEnv *jenv, jobject jobj, jlong ptr, jint useUniColor)
{
	TriangleShape* triangleShape = (TriangleShape*) ptr;
	triangleShape->useUniColor(useUniColor);
}

JNIEXPORT jint        JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_isUsingUniColorTriangleShape(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	TriangleShape* triangleShape = (TriangleShape*) ptr;
	return triangleShape->isUsingUniColor();
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_getUniColorTriangleShape(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	TriangleShape* triangleShape = (TriangleShape*) ptr;
	Color c =  triangleShape->getUniColor();

	jfloatArray result = jenv->NewFloatArray(4);
	float pc[] = {c.r, c.g, c.b, c.a};

	jenv->SetFloatArrayRegion(result, 0, 4, pc);

	return result;
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_getColorTriangleShape(JNIEnv *jenv, jobject jobj, jlong ptr, jint vertex)
{
	TriangleShape* triangleShape = (TriangleShape*) ptr;
	Color c =  triangleShape->getColor(vertex);

	jfloatArray result = jenv->NewFloatArray(4);
	float pc[] = {c.r, c.g, c.b, c.a};

	jenv->SetFloatArrayRegion(result, 0, 4, pc);

	return result;
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_getPositionTriangleShape(JNIEnv *jenv, jobject jobj, jlong ptr, jint vertex)
{
	TriangleShape* triangleShape = (TriangleShape*) ptr;
	glm::vec3 v=  triangleShape->getPosition(vertex);

	jfloatArray result = jenv->NewFloatArray(3);
	float pv[] = {v.x, v.y, v.z};

	jenv->SetFloatArrayRegion(result, 0, 3, pv);
	return result;
}
