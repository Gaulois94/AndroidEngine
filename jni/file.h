#ifndef FILE_INCLUDE
#define FILE_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <jni.h>
#include "logger.h"

FILE* openFile(JNIEnv* env, jobject context, const char* path, const char* mode);
FILE* openFile(JNIEnv* env, jobject context, int id, const char* mode);
char* getLine(FILE* file, int maxCharacter=128);

#endif
