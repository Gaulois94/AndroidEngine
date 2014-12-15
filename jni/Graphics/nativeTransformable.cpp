#include "nativeTransformable.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Transformable_createTransformable(JNIEnv* jenv, jobject jobj)
{
	Transformable* trans = new Transformable();
	return (jlong)trans;
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Transformable_destroyTransformable(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	Transformable* trans = (Transformable*) ptr;
	delete trans;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_moveTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, jfloatArray move)
{
	Transformable* trans = (Transformable*) transPtr;
	jfloat* m = jenv->GetFloatArrayElements(move, 0);
	trans->move(glm::vec3(m[0], m[1], m[2]));		
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_setPositionTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, jfloatArray position)
{
	Transformable* trans = (Transformable*) transPtr;
	jfloat* p = jenv->GetFloatArrayElements(position, 0);
	trans->setPosition(glm::vec3(p[0], p[1], p[2]));		
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_rotateTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, float angle, jfloatArray rotate)
{
	Transformable* trans = (Transformable*) transPtr;
	jfloat* r = jenv->GetFloatArrayElements(rotate, 0);
	trans->rotate(angle, glm::vec3(r[0], r[1], r[2]));		
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_setRotationTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, float angle, jfloatArray rotate)
{
	Transformable* trans = (Transformable*) transPtr;
	jfloat* r = jenv->GetFloatArrayElements(rotate, 0);
	trans->setRotate(angle, glm::vec3(r[0], r[1], r[2]));		
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_scaleTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, jfloatArray scale)
{
	Transformable* trans = (Transformable*) transPtr;
	jfloat* s = jenv->GetFloatArrayElements(scale, 0);
	trans->scale(glm::vec3(s[0], s[1], s[2]));		
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_setScaleTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, jfloatArray scale)
{
	Transformable* trans = (Transformable*) transPtr;
	jfloat* s = jenv->GetFloatArrayElements(scale, 0);
	trans->setScale(glm::vec3(s[0], s[1], s[2]));		
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_setSphericCoordinateTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, float r, float theta, float phi)
{
	Transformable* trans = (Transformable*) transPtr;
	trans->setSphericCoordinate(r, theta, phi);		
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_rotatePhiTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, float phi)
{
	Transformable* trans = (Transformable*) transPtr;
	trans->rotatePhi(phi);
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Transformable_rotateThetaTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr, float theta)
{
	Transformable* trans = (Transformable*) transPtr;
	trans->rotateTheta(theta);
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Transformable_getPositionTranformable(JNIEnv* jenv, jobject jobj, jlong transPtr)
{
	Transformable* trans = (Transformable*) transPtr;
	glm::vec3          s = trans->getPosition();

	jfloatArray result;
	result = jenv->NewFloatArray(3);
	float v[3];

	for(int i=0; i < 3; i++)
		v[i] = s[i];

	jenv->SetFloatArrayRegion(result, 0, 3, v);

	return result;
}

JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Transformable_getSphericCoordinateTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr)
{
	Transformable* trans = (Transformable*) transPtr;
	SphericCoord       s = trans->getSphericCoord();

	jfloatArray result;
	result = jenv->NewFloatArray(3);

	float v[3] = {s.r, s.theta, s.phi};
	jenv->SetFloatArrayRegion(result, 0, 3, v);

	return result;
}
JNIEXPORT jfloatArray JNICALL Java_com_gaulois94_Graphics_Transformable_getEulerRotationTransformable(JNIEnv* jenv, jobject jobj, jlong transPtr)
{
	Transformable* (trans) = (Transformable*) transPtr;
	EulerRotation        e = trans->getEulerRotation();

	jfloatArray result;
	result = jenv->NewFloatArray(3);

	float v[3] = {e.roll, e.pitch, e.yaw};
	jenv->SetFloatArrayRegion(result, 0, 3, v);

	return result;
}
