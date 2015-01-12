#ifndef READFILE_INCLUDE
#define READFILE_INCLUDE

#include <iostream>
#include <string>
#include <unistd.h>
#include "stdlib.h"
#include "stdio.h"
#include "jni.h"
#include "logger.h"

class File
{
	public:
		File(FILE* file, int size, int offset);
		File(JNIEnv* env, jobject context, int id, const char* mode);
		File(JNIEnv* env, jobject context, const char* path, const char* mode);
		~File();
		char* readLine();
		char readChar();
	private:
		FILE* m_file;
		int   m_size;
		int   m_offset;
		int   m_pos;
};

#endif
