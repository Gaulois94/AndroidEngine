#ifndef JNIMADEOF_INCLUDE
#define JNIMADEOF_INCLUDE

#include <jni.h>
#include "logger.h"
#include <string>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>

/** \brief Base class of JNI Objects
 * */
class JniMadeOf
{
	public:
		/** \brief JniMadeOf constructor. Don't do anything in particular.
		 * */
		JniMadeOf();
		virtual ~JniMadeOf();

		/** \brief Tell if the methodName exist in the object in java. Used for 'onFunc' polymorphisme for example
		 * \param methodName the method name
		 * \param signature the method signature*/
		bool methodExist(char* methodName, char* signature);

		/** \brief Set the java object associated with the C++object
		 * \param jobj the new java object*/
		void setJobject(jobject jobj);

		/** \brief Return the java object
		 * \return the java object associated with this C++ object*/
		jobject getJobject() const;

		static JNIEnv* getJEnv();
		static jclass  getClass(const std::string& className);

		//Static Variables
		static JNIEnv* jenv; /* <the java environment. Should be constante while the application run.*/
		static AAssetManager* assetsManager;
		static jobject context;
		static jobject jassetsManager;
		static jobject jclassLoader;
		static JavaVM* vm;
	protected:
		jobject m_obj;
};

#endif
