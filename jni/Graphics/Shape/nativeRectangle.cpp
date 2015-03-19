#include "Shape/nativeRectangle.h"

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Shape_createRectangle(JNIEnv* jenv, jclass jcls, jlong matPtr, int x, int y)
{
	Rectangle* rect = new Rectangle((Material*)matPtr, x, y);
	return rect;
}
