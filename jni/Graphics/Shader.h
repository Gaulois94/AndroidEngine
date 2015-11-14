#ifndef SHADER_INCLUDE
#define SHADER_INCLUDE

#define ERROR_MAX_LENGTH 500

#include <GLES2/gl2.h>
#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include "ResourcesManager.h"
#include "logger.h"
#include "File.h"
#include "JniMadeOf.h"

/** \brief A graphic program.*/
class Shader : JniMadeOf
{
	public:
		/** \brief the shader constructor. Should never be called alone (use loader functions)*/
		Shader();
		~Shader();

		/** \brief get the program ID stored in the graphic memory of this shader.
		 * \return the program ID */
		int getProgramID() const;

		/** \brief get the vertex ID stored in the graphic memory of this shader.
		 * \return the vertex ID */
		int getVertexID() const;

		/** \brief get the fragment ID stored in the graphic memory of this shader.
		 * \return the fragment ID */
		int getFragID() const;

		/** \brief create a shader from a vertex and a fragment file.
		 * \param vertexFile the vertex file.
		 * \param fragmentFile the fragment file.*/
		static Shader* loadFromFiles(File vertexFile, File fragFile);

		/** \brief create a shader from a vertex and a fragment string.
		 * \param vertexString the vertex string.
		 * \param fragmentString the fragment string.
		 * */
		static Shader* loadFromStrings(const std::string& vertexString, const std::string& fragString);
		static ResourcesManager<Shader*> shaders; 
	private:
		GLuint m_programID;
		GLuint m_vertexID;
		GLuint m_fragID;

		/** \brief Bind the attributes key string by an ID */
		static int loadShader(const std::string& code, int type);
};

#endif
