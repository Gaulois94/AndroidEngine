#ifndef BMP_INCLUDE
#define BMP_INCLUDE

#include <stdlib.h>
#include <android/bitmap.h>
#include <jni.h>
#include "JniMadeOf.h"
#include "logger.h"

class Bitmap : JniMadeOf
{
	public:
		Bitmap(unsigned char* p, AndroidBitmapInfo& info);
		~Bitmap();
		void invertPixels();

		unsigned char* pixels;
		AndroidBitmapInfo info;
};

#endif
