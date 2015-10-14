#ifndef DEF_NATIVESELECTANIMATION
#define DEF_NATIVESELECTANIMATION

#include "SelectAnimation.h"
#include <jni.h>
#include <vector>
#include "Rectangle2.h"

extern "C"
{
	JNIEXPORT long JNICALL Java_com_gaulois94_Graphics_SelectAnimation_createSelectAnimation(JNIEnv* jenv, jclass cls, long parent, long material, long texture, jintArray rectAnimation, int rectSize, int nbFrame);
}

#endif
