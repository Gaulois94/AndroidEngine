#include "Shape/nativeTriangleShape.h"

JNIEXPORT jlong       JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_createTriangleShape(JNIEnv *jenv, jclass jcls, jlong parent, jlong material, jfloatArray vertexCoords, jfloatArray normalCoords, jint nbVertex, jint mode)
{
	float* pv = jenv->GetFloatArrayElements(vertexCoords, 0);
	float* pn = jenv->GetFloatArrayElements(normalCoords, 0);

	TriangleShape* result = new TriangleShape((Updatable*)parent, (Material*)material, pv, pn, nbVertex, mode);
	jenv->ReleaseFloatArrayElements(vertexCoords, pv, 0);
	jenv->ReleaseFloatArrayElements(normalCoords, pn, 0);

	return (long)result;
}

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_setDatasTriangleShape(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray vertexCoords, jfloatArray normalCoords, jint nbVertex)
{
	float* pv = jenv->GetFloatArrayElements(vertexCoords, 0);
	float* pn = jenv->GetFloatArrayElements(normalCoords, 0);

	TriangleShape* triangleShape = (TriangleShape*) ptr;
	triangleShape->setDatas(pv, pn, nbVertex);

	jenv->ReleaseFloatArrayElements(vertexCoords, pv, 0);
	jenv->ReleaseFloatArrayElements(normalCoords, pn, 0);
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

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_setNormalTriangleShape(JNIEnv *, jobject, jlong, jfloatArray)
{

}

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_setDrawOrderTriangleShape(JNIEnv*, jobject, jint, jint)
{

}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Shape_TriangleShape_getPositionVertexTriangleShape(JNIEnv *jenv, jobject jobj, jlong ptr, jint vertex)
{
	TriangleShape* triangleShape = (TriangleShape*) ptr;
	glm::vec3 v=  triangleShape->getPositionVertex(vertex);

	jfloatArray result = jenv->NewFloatArray(3);
	float pv[] = {v.x, v.y, v.z};

	jenv->SetFloatArrayRegion(result, 0, 3, pv);
	return result;
}
