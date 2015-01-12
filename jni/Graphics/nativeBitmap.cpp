#include "nativeBitmap.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Bitmap_createBitmap(JNIEnv* jenv, jclass jcls, jobject bmp)
{
	AndroidBitmapInfo bmpInfo;
	AndroidBitmap_getInfo(jenv, bmp, &bmpInfo);

	void* buffer;
	AndroidBitmap_lockPixels(jenv, bmp, &buffer);

	unsigned char* pixels = (unsigned char*) buffer;

	Bitmap* ptr = new Bitmap(pixels, bmpInfo);
	ptr->invertPixels();

	AndroidBitmap_unlockPixels(jenv, bmp);
	return (jlong)ptr;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Bitmap_invertPixelsBitmap(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	Bitmap* bmp = (Bitmap*) ptr;
	bmp->invertPixels();
}
