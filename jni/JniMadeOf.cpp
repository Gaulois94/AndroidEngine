#include "JniMadeOf.h"

JNIEnv* JniMadeOf::jenv = 0;
jobject JniMadeOf::context = 0;
jobject JniMadeOf::jassetsManager = 0;
AAssetManager* JniMadeOf::assetsManager = NULL;

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
