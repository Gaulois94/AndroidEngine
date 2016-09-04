#include "JniMadeOf.h"

JNIEnv* JniMadeOf::jenv = 0;
jobject JniMadeOf::context = 0;
jobject JniMadeOf::jassetsManager = 0;
AAssetManager* JniMadeOf::assetsManager = NULL;
JavaVM* JniMadeOf::vm = 0;

JniMadeOf::JniMadeOf(){}

JniMadeOf::~JniMadeOf(){}

bool JniMadeOf::methodExist(char* methodName, char* signature)
{
	if(m_obj == 0)
		return false;
	jclass objClass = jenv->GetObjectClass(m_obj);
	return (jenv->GetMethodID(objClass, methodName, signature) != 0);
}

jobject JniMadeOf::getJobject() const
{
	return m_obj;
}

void JniMadeOf::setJobject(jobject jobj)
{
	m_obj = jobj;
}

JNIEnv* JniMadeOf::getJEnv()
{
	JNIEnv* env;
	if (JniMadeOf::vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
		LOG_ERROR("Failed to get the environment using GetEnv()");


	if (JniMadeOf::vm->AttachCurrentThread(&env, NULL) < 0)
		LOG_ERROR("Failed to get the environment using AttachCurrentThread()");

	return env;
}
