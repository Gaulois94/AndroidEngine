#include "nativeSelectAnimation.h"

JNIEXPORT long JNICALL Java_com_gaulois94_Graphics_SelectAnimation_createSelectAnimation(JNIEnv* jenv, jclass cls, long parent, long material, long texture, jintArray rectAnimation, int rectSize, int nbFrame)
{
	int* r = jenv->GetIntArrayElements(rectAnimation, 0);
	std::vector<Rectangle2ui> v;
	for(int i=0; i < rectSize; i++)
	{
		int rIndice = 4*i;
		v.push_back(Rectangle2ui(r[rIndice], r[rIndice+1], r[rIndice+2], r[rIndice+3]));
	}

	jenv->ReleaseIntArrayElements(rectAnimation, r, 0);
	SelectAnimation* result = new SelectAnimation((Updatable*)parent, (Material*)material, (Texture*)texture, v, nbFrame);
	return (long)result;
}
