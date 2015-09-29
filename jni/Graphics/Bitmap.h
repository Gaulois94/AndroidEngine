#ifndef BMP_INCLUDE
#define BMP_INCLUDE

#include <stdlib.h>
#include <android/bitmap.h>
#include <jni.h>
#include "JniMadeOf.h"
#include "logger.h"

/** \brief Bitmap class */
class Bitmap : JniMadeOf
{
	public:
		/** \brief Bitmap constructor from bitmap info and an array of pixels.
		 * \param p array of pixels. Each value correspond to a color on a pixel (3 values per pixels)
		 * \param info the bitmap information. */
		Bitmap(unsigned char* p, AndroidBitmapInfo& info);

		~Bitmap();

		/** \brief Mirror the pixels from the axis y (pass from SDL bitmap pixels to opengl pixels and vice versa) */
		void invertPixels();

		unsigned char* pixels; /** <The array of pixels */
		AndroidBitmapInfo info; /** <The bitmap information */
};

#endif
