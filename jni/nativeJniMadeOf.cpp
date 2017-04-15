#include "nativeJniMadeOf.h"

JNIEXPORT void JNICALL Java_com_gaulois94_JniMadeOf_destroyJniMadeOf(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	JniMadeOf* obj = (JniMadeOf*) ptr;
	delete obj;
}

JNIEXPORT void JNICALL Java_com_gaulois94_JniMadeOf_setJobjectJniMadeOf(JNIEnv* jenv, jlong ptr, jobject jobj)
{
	JniMadeOf* jniMadeOf = (JniMadeOf*) ptr;
	jniMadeOf->setJobject(jenv->NewGlobalRef(jobj));
}

JNIEXPORT void JNICALL Java_com_gaulois94_JniMadeOf_initJniMadeOf(JNIEnv* jenv, jclass jcls, jobject assetManager, jobject context, jobject classLoader)
{
	JniMadeOf::jenv           = jenv;
	JniMadeOf::assetsManager  = AAssetManager_fromJava(jenv, assetManager);
	JniMadeOf::jassetsManager = jenv->NewGlobalRef(assetManager);
	JniMadeOf::context        = jenv->NewGlobalRef(context);
	JniMadeOf::jclassLoader   = jenv->NewGlobalRef(classLoader);


	//Get the ClassLoader
	
	

	jenv->GetJavaVM(&JniMadeOf::vm);
}
