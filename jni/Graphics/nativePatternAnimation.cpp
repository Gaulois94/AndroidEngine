#include "nativePatternAnimation.h"

JNIEXPORT long JNICALL Java_com_gaulois94_PatternAnimation_createPatternAnimation(JNIEnv* jenv, jclass jcls, long parent, long material, long texture, jintArray pos, jintArray pad, jintArray size, jintArray n, int nSprite)
{
	int *posV  = jenv->GetIntArrayElements(pos, 0);
	int *padV  = jenv->GetIntArrayElements(pad, 0);
	int *sizeV = jenv->GetIntArrayElements(size, 0);
	int *nV    = jenv->GetIntArrayElements(n, 0);

	PatternAnimation* result = 
		new PatternAnimation(Vector2ui(posV[0], posV[1]), Vector2ui(padV[0], padV[1]),
							 Vector2ui(sizeV[0], sizeV[1]), Vector2ui(nV[0], nV[1]), nSprite);

	jenv->ReleaseIntArrayElements(pos, posV, 0);
	jenv->ReleaseIntArrayElements(pad, padV, 0);
	jenv->ReleaseIntArrayElements(size, sizeV, 0);
	jenv->ReleaseIntArrayElements(n, nV, 0);

	return result;
}
