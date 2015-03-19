#include <jni.h>
#include "Shape/Rectangle.h"
#include "Materials/Material.h"

extern "C"
{
	JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Shape_createRectangle(JNIEnv* jenv, jclass jcls, jlong mtlPtr, int x, int y);
};
