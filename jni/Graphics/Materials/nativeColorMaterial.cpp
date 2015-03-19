#include "Materials/nativeColorMaterial.h"

JNIEXPORT long        JNICALL Java_com_gaulois94_Graphics_Materials_ColorMaterial_createColorMaterial(JNIEnv *jenv, jclass jcls, jfloatArray color, int nbVertex)
{
	jfloat* c = jenv->GetFloatArrayElements(color, 0);
	ColorMaterial* m = new ColorMaterial(c, nbVertex);
	jenv->ReleaseFloatArrayElements(color, c, 0);

	return (long)m;
}

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Materials_ColorMaterial_setColorColorMaterial(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray color, int nbVertex)
{

	jfloat* c = jenv->GetFloatArrayElements(color, 0);
	ColorMaterial* m = (ColorMaterial*)ptr;
	m->setColor(c, nbVertex);
	jenv->ReleaseFloatArrayElements(color, c, 0);
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Materials_ColorMaterial_getColorColorMaterial(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	ColorMaterial* m = (ColorMaterial*)ptr;
	jfloatArray result = jenv->NewFloatArray(3);

	Color* color = m->getColor();

	float c[4*m->getNbVertex()];

	for(int i=0; i < m->getNbVertex(); i++)
		color[i].getFloatArray(&(c[4*i]));

	jenv->SetFloatArrayRegion(result, 0, 4*m->getNbVertex(), c);
	return result;
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Materials_ColorMaterial_getColorColorMaterial(JNIEnv *jenv, jobject jobj, jlong ptr, int vertex)
{
	ColorMaterial* m = (ColorMaterial*)ptr;
	jfloatArray result = jenv->NewFloatArray(3);

	Color color = m->getColor();

	float c[4];

	color.getFloatArray(c);

	jenv->SetFloatArrayRegion(result, 0, 4, c);
	return result;
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Materials_ColorMaterial_getNbVertexColorMaterial(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	ColorMaterial* m = (ColorMaterial*)ptr;
	return m->getNbVertex();
}
