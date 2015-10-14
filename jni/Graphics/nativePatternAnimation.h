#ifndef DEF_NATIVEPATTERNANIMATION
#define DEF_NATIVEPATTERNANIMATION

extern "C"
{
	JNIEXPORT long JNICALL Java_com_gaulois94_PatternAnimation_createPatternAnimation(JNIEnv* jenv, jclass jcls, long parent, long material, long texture, jintArray pos, jintArray pad, jintArray size, jintArray n, int nSprite);
}

#endif
