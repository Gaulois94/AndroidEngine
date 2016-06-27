/** \file File.h
 * \brief File manager
 */

#ifndef READFILE_INCLUDE
#define READFILE_INCLUDE

#define LINE_BUFFER 1024

#include <iostream>
#include <string>
#include <unistd.h>
#include "stdlib.h"
#include "stdio.h"
#include "jni.h"
#include "logger.h"
#include "JniMadeOf.h"

/** \class File
 * \brief Files manager
 * This class manage files*/
class File
{
	public:
		/** \brief Create a File object from an existing FILE C struct
		 * \param file   The C struct file whose contain information about the file
		 * \param size   The size of the file
		 * \param offset The offset from where the file start
		 * */ 
		File(FILE* file, int size, int offset);

		/** \brief Create a File object from a raw resource id
		 * \param env     The java environment
		 * \param context The application context (the main Application)
		 * \param id      The raw resource id
		 * \param mode    The file mode access
		 */
		File(JNIEnv* env, jobject context, int id, const char* mode);

		/** \brief Create a File object from an assets path on the assets directory
		 * \param env     The java environment
		 * \param context The application context (the main Application)
		 * \param path    The file path on the assets directory
		 * \param mode    The file mode access
		 */
		File(JNIEnv* env, jobject context, const char* path, const char* mode);
		
		/** \brief Create a file from an assets path on the assets directory.
		 * Do the same job than its version with JNIEnv and the context with their default value (from JniMadeOf)
		 * \param path The file path on the assets directory
		 * \param mode The file mode access*/
		File(const char* path, const char* mode);

		~File();

		/** \brief  Read the next file line.
		 * \return The file line.
		 */
		char* readLine();

		/** \brief  Read the next file character.
		 * \return The file character.
		 */
		char readChar();

		/** \brief Get the file path is the file is an asset
		 * \return The file path from the asset directory
		 */
		const std::string& getPath() const;

		static std::string getFilesPath(const std::string& fileName);
	private:
		FILE* m_file;
		uint32_t   m_size;
		uint32_t   m_offset;
		uint32_t   m_pos;
		std::string m_path;
};

#endif
