#include "nativePatternAnimation.h"

JNIEXPORT long JNICALL Java_com_gaulois94_PatternAnimation_createPatternAnimation(JNIEnv* jenv, jclass jcls, long parent, long material, long texture, jintArray pos, jintArray pad, jintArray size, int nX, int nSprite, int nbFrame)
{
	int *posV  = jenv->GetIntArrayElements(pos, 0);
	int *padV  = jenv->GetIntArrayElements(pad, 0);
	int *sizeV = jenv->GetIntArrayElements(size, 0);

	PatternAnimation* result = 
		new PatternAnimation((Updatable*)parent, (Material*)material, (Texture*)texture,
							 Vector2ui(posV[0], posV[1]), Vector2ui(padV[0], padV[1]),
							 Vector2ui(sizeV[0], sizeV[1]), nX,
							 nSprite, nbFrame);

	jenv->ReleaseIntArrayElements(pos, posV, 0);
	jenv->ReleaseIntArrayElements(pad, padV, 0);
	jenv->ReleaseIntArrayElements(size, sizeV, 0);

	return (long)result;
}
