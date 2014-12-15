#ifndef BITMAP_INCLUDE
#define BITMAP_INCLUDE

#include <stdio.h>
#include <android/bitmap.h>
#include <jni.h>

class Bitmap
{
	public:
		Bitmap(unsigned char* p, AndroidBitmapInfo& info);
		void invertPixels()

		unsigned char* pixels;
		AndroidBitmapInfo info;
};

#endif
