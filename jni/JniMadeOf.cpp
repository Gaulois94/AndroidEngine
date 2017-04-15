#include "JniMadeOf.h"

JNIEnv* JniMadeOf::jenv                 = 0;
jobject JniMadeOf::context              = 0;
jobject JniMadeOf::jassetsManager       = 0;
jobject JniMadeOf::jclassLoader         = 0;
AAssetManager* JniMadeOf::assetsManager = NULL;
JavaVM* JniMadeOf::vm                   = 0;

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
	int getEnvStat = JniMadeOf::vm->GetEnv((void**)&env, JNI_VERSION_1_4);

	if(getEnvStat == JNI_EDETACHED)
	{
		LOG_ERROR("Jni environnement not attached");
		if (JniMadeOf::vm->AttachCurrentThread(&env, NULL) < 0)
			LOG_ERROR("Failed to get the environment using AttachCurrentThread()");
	}

	else if(getEnvStat == JNI_EVERSION)
		LOG_ERROR("GetEnv : version not supported");

	else if(getEnvStat != JNI_OK)
		LOG_ERROR("Fail to get the JNI Environnement");

	return env;
}

jclass JniMadeOf::getClass(const std::string& className)
{
	JNIEnv* env = JniMadeOf::getJEnv();
	jclass loaderClass = env->GetObjectClass(JniMadeOf::jclassLoader);
	jmethodID findClassMethod = env->GetMethodID(loaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");


    return (jclass)env->CallObjectMethod(JniMadeOf::jclassLoader, findClassMethod, env->NewStringUTF(className.c_str()));
}
