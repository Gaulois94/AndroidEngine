#include "Materials/nativeMaterial.h"

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Materials_Material_enableShaderMaterial(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Material* material = (Material*)ptr;
	material->enableShader();
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Materials_Material_bindTextureMaterial(JNIEnv *jenv, jobject jobj, jlong ptr, jlong texturePtr)
{
	Material* material = (Material*)ptr;
	material->bindTexture((Texture*)texturePtr);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Materials_Material_initMaterial(JNIEnv *jenv, jobject jobj, jlong ptr, jlong renderPtr, jfloatArray mvp, jfloatArray modelMatrix)
{
	Material* material = (Material*)ptr;

	jfloat* m = jenv->GetFloatArrayElements(mvp, 0);
	jfloat* m2 = jenv->GetFloatArrayElements(modelMatrix, 0);
	material->init(*(Render*)renderPtr, glm::make_mat4(m), glm::make_mat4(m2));
	jenv->ReleaseFloatArrayElements(mvp, m, 0);
	jenv->ReleaseFloatArrayElements(modelMatrix, m2, 0);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Materials_Material_unbindTextureMaterial(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Material* material = (Material*)ptr;
	material->unbindTexture();
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Materials_Material_disableShaderMaterial(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Material* material = (Material*)ptr;
	material->disableShader();
}

JNIEXPORT long JNICALL Java_com_gaulois94_Graphics_Materials_Material_getShaderMaterial(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Material* material = (Material*)ptr;
	return (long)material->getShader();	
}
