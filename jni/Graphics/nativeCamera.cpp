#include "nativeCamera.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Camera_createCamera(JNIEnv *jenv, jclass jcls)
{
	Camera* camera = new Camera();
	camera->setJobject(jobject);
	return (jlong) camera;
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Camera_getPositionCamera(JNIEnv *jenv, jobject jobj, jlong ptr)
{
	Camera* camera     = (Camera*) ptr;
	glm::vec3 position = camera->getPosition();

	jfloatArray result = jenv->NewFloatArray(3);
	float p[3]         = {position.x, position.y, position.z};
	jenv->SetFloatArrayRegion(result, 0, 3, p);

	return result;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Camera_lookAtCamera(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray position, jfloatArray target)
{
	float* p = jenv->GetFloatArrayElements(position, 0);
	float* t = jenv->GetFloatArrayElements(target, 0);

	Camera* camera = (Camera*) ptr;
	camera->lookAt(glm::vec3(p[0], p[1], p[2]), glm::vec3(t[0], t[1], t[2]));

	jenv->ReleaseFloatArrayElements(position, p, 0);
	jenv->ReleaseFloatArrayElements(target, t, 0);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Camera_setPositionCamera(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray position)
{
	float* p = jenv->GetFloatArrayElements(position, 0);

	Camera* camera = (Camera*) ptr;
	camera->setPosition(glm::vec3(p[0], p[1], p[2]));

	jenv->ReleaseFloatArrayElements(position, p, 0);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Camera_setOrientationCamera(JNIEnv *jenv, jobject jobj, jlong ptr, jfloatArray orientation)
{
	float* o = jenv->GetFloatArrayElements(orientation, 0);

	Camera* camera = (Camera*) ptr;
	camera->setOrientation(glm::vec3(o[0], o[1], o[2]));

	jenv->ReleaseFloatArrayElements(orientation, o, 0);
}
