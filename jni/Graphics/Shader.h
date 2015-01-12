#ifndef SHADER_INCLUDE
#define SHADER_INCLUDE

#define ERROR_MAX_LENGTH 500

#include <GLES2/gl2.h>
#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include "logger.h"
#include "File.h"
#include "JniMadeOf.h"

class Shader : JniMadeOf
{
	public:
		Shader();
		~Shader();
		int getProgramID();
		int getVertexID();
		int getFragID();

		static Shader* loadFromFiles(File vertexFile, File fragFile);
		static Shader* loadFromFiles(File vertexFile, File fragFile, const std::map<std::string, int>& attrib); 

		static Shader* loadFromStrings(const std::string& vertexString, const std::string& fragString);
		static Shader* loadFromStrings(const std::string& vertexString, const std::string& fragString, const std::map<std::string, int>& attrib);

	private:
		GLuint m_programID;
		GLuint m_vertexID;
		GLuint m_fragID;

		void bindAttribLocation(const std::map<std::string, int>& attrib);
		static int loadShader(const std::string& code, int type);
};

#endif
