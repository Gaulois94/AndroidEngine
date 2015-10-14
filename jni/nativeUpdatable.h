#ifndef DEF_NATIVEUPDATBLE_INCLUDE
#define DEF_NATIVEUPDATBLE_INCLUDE

extern "C"
{
	JNIEXPORT jlong   JNICALL Java_com_gaulois94_Updatable_createUpdatable(JNIEnv* jenv, jclass jcls, jlong parent);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_updateFocusUpdatable(JNIEnv* jenv, jlong ptr, jlong renderer);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_onFocusUpdatable(JNIEnv* jenv, jlong ptr, jlong renderer);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_updateUpdatable(JNIEnv* jenv, jlong ptr, jlong render);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_onUpdateUpdatable(JNIEnv* jenv, jlong ptr, jlong render);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_addChildUpdatable(JNIEnv* jenv, jlong ptr, jlong child, int pos);
	JNIEXPORT void    JNICALL Java_com_gaulois94_Updatable_setParentUpdatable(JNIEnv* jenv, jlong ptr, jlong parent, int pos);
	JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_removeChildUpdatable(JNIEnv* jenv, jlong ptr, jlong child);
	JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_removeChildUpdatable(JNIEnv* jenv, jlong ptr, int pos);
	JNIEXPORT bool    JNICALL Java_com_gaulois94_Updatable_isChildUpdatable(JNIEnv* jenv, jlong ptr, jlong child);
	JNIEXPORT jobject JNICALL Java_com_gaulois94_Updatable_getParentUpdatable(JNIEnv* jenv, jlong ptr);
}

#endif
