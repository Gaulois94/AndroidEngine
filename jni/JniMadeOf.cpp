#include "JniMadeOf.h"

JniMadeOf::JniMadeOf(){}

JniMadeOf::~JniMadeOf(){}

bool JniMadeOf::methodExist(char* methodName, char* signature)
{
	return (GetMethodID(jniEnv, m_obj, methodName, signature) != NULL);
}
