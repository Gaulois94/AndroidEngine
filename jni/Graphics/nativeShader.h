#ifndef NATIVE_SHADER_INCLUDE
#define NATIVE_SHADER_INCLUDE

#include <jni.h>
#include <map>
#include <stdio.h>
#include <string>
#include "Shader.h"
#include "File.h"

extern "C"
{
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Shader_loadFromFilesShader(JNIEnv* jenv, jclass jcls, jobject context, jstring vertexPath, jstring fragPath, jobject attrib, jobjectArray keys, jobjectArray values);
	JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Shader_loadFromStringShader(JNIEnv* jenv, jclass jcls, jstring vertexCode, jstring fragCode, jobject attrib, jobjectArray keys, jobjectArray values);
	JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Shader_getProgramIDShader(JNIEnv* jenv, jobject jobj, jlong ptr);
	JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Shader_getVertexIDShader(JNIEnv* jenv, jobject jobj, jlong ptr);
	JNIEXPORT jint JNICALL Java_com_gaulois94_Graphics_Shader_getFragIDShader(JNIEnv* jenv, jobject jobj, jlong ptr);

	std::map<std::string, int> makeMap(JNIEnv* jenv, jobjectArray keys, jobjectArray values);
};

#endif
