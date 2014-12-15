#include "nativeBitmap.h"

JNIEXPORT jlong JNICALL Java_com_gaulois94_Graphics_Bitmap_createBitmap(JNIEnv* jenv, jobject jobj, jobject bmp)
{
	AndroidBitmapInfo bmpInfo;
	AndroidBitmap_getInfo(jenv, bmp, &bmpInfo);

	void* buffer;
	AndroidBitmap_lockPixels(jenv, bmp, &buffer);

	unsigned char* pixels = (unsigned char*) buffer;

	Bitmap* ptr = new Bitmap(pixels, bmpInfo);

	AndroidBitmap_unlockPixels(jenv, bmp);

	return ptr;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Bitmap_destroyBitmap(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	Bitmap* bmp = (Bitmap*) ptr;
	delete bmp;
}

JNIEXPORT void JNICALL Java_com_gaulois94_Graphics_Bitmap_invertPixelsBitmap(JNIEnv* jenv, jobject jobj, jlong ptr)
{
	Bitmap* bmp = (Bitmap*) ptr;
	bmp->invertPixels();
}
