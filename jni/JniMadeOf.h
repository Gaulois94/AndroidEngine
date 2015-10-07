#ifndef JNIMADEOF_INCLUDE
#define JNIMADEOF_INCLUDE

#include <jni.h>

enum MethodType
{
}

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

		static JNIEnv* jenv; /* <the java environment. Should be constante while the application run.*/
	private:
		jobject m_obj;
};

#endif
