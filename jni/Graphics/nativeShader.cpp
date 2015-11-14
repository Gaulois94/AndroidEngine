#include "nativeShader.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Shader_loadFromFilesShader(JNIEnv* jenv, jclass jcls, jobject context, jstring vertexPath, jstring fragPath, jobject attrib, jobjectArray keys, jobjectArray values)
{
	File vertexFile  = File(jenv, context, jenv->GetStringUTFChars(vertexPath, 0), "r");
	File fragFile    = File(jenv, context, jenv->GetStringUTFChars(fragPath, 0), "r");

	Shader* shader = NULL;
	if(attrib == NULL)
		shader = Shader::loadFromFiles(vertexFile, fragFile);
	else
		shader = Shader::loadFromFiles(vertexFile, fragFile);

	return (jlong) shader;
}

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Shader_loadFromStringShader(JNIEnv* jenv, jclass jcls, jstring vertexCode, jstring fragCode, jobject attrib, jobjectArray keys, jobjectArray values)
{
	if(attrib == NULL)
		return (jlong) Shader::loadFromStrings(std::string(jenv->GetStringUTFChars(vertexCode, 0)), 
				std::string(jenv->GetStringUTFChars(fragCode, 0)));
	return (jlong) Shader::loadFromStrings(std::string(jenv->GetStringUTFChars(vertexCode, 0)), 
			std::string(jenv->GetStringUTFChars(fragCode, 0)));
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Shader_getProgramIDShader(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	Shader* shader = (Shader*) ptr;
	return shader->getProgramID();
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Shader_getVertexIDShader(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	Shader* shader = (Shader*) ptr;
	return shader->getVertexID();
}

JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Shader_getFragIDShader(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	Shader* shader = (Shader*) ptr;
	return shader->getFragID();
}

std::map<std::string, int> makeMap(JNIEnv* jenv, jobjectArray keys, jobjectArray values)
{
	std::map<std::string, int> map;
	int length = jenv->GetArrayLength(keys);
	for(int i=0; i < length; i++)
	{
		jstring k          = (jstring) jenv->GetObjectArrayElement(keys, i);
		jobject o          = (jobject) jenv->GetObjectArrayElement(values, i);

		jclass integer     = jenv->FindClass("java/lang/Integer");
		jmethodID intValue = jenv->GetMethodID(integer, "intValue", "()I");
		jint v             = jenv->CallIntMethod(o, intValue);

		const char* key          = jenv->GetStringUTFChars(k, 0);
		map.insert(std::pair<std::string, int>(std::string(key), v));
		jenv->ReleaseStringUTFChars(k, key);
	}

	return map;
}
