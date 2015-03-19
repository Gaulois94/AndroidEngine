#include "Materials/nativeUniColorMaterial.h"

JNIEXPORT jlong        JNICALL Java_com_gaulois94_Graphics_Materials_UniColorMaterial_createUniColorMaterial(JNIEnv *jenv, jclass jcls, jfloatArray color)
{
	jfloat* c = jenv->GetFloatArrayElements(color, 0);
	UniColorMaterial* m = new UniColorMaterial(c);
	jenv->ReleaseFloatArrayElements(color, c, 0);

	return (long)m;
}

JNIEXPORT void        JNICALL Java_com_gaulois94_Graphics_Materials_UniColorMaterial_setColorUniColorMaterial(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray color)
{

	jfloat* c = jenv->GetFloatArrayElements(color, 0);
	UniColorMaterial* m = (UniColorMaterial*)ptr;
	m->setColor(c);
	jenv->ReleaseFloatArrayElements(color, c, 0);
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Materials_UniColorMaterial_getColorUniColorMaterial(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	UniColorMaterial* m = (UniColorMaterial*)ptr;
	jfloatArray result = jenv->NewFloatArray(3);

	Color color = m->getColor();

	float c[4];
	color.getFloatArray(c);

	jenv->SetFloatArrayRegion(result, 0, 4, c);
	return result;
}
