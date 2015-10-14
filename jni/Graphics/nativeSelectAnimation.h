#ifndef DEF_SELECTANIMATION
#define DEF_SELECTANIMATION

extern "C"
{
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_SelectAnimation_createSelectAnimation(JNIEnv* jenv, jclass cls, long parent, long material, long texture, jintArray rectAnimation, int rectSize);
}

#endif
