#include "Bitmap.h"

Bitmap::Bitmap(unsigned char* p, AndroidBitmapInfo& inf)
{
	pixels = (unsigned char*)malloc(4 * inf.width * inf.height * sizeof(unsigned char));
	for(unsigned int i=0; i < inf.height; i++)
		for(unsigned int j=0; j < 4*inf.width; j++)
			pixels[4*inf.width*i + j] = p[4*inf.width*i + j];

	info = inf;
}

Bitmap::~Bitmap()
{
	free(pixels);
}

void Bitmap::invertPixels()
{
	unsigned char* oldPixels = pixels;
	pixels = (unsigned char*)malloc(4*info.width*info.height*sizeof(unsigned char));

	for(unsigned int i=0; i < info.height; i++)
		for(unsigned int j=0; j < 4*info.width; j++)
			pixels[4*info.width*i + j] = oldPixels[4*info.width*(info.height-1-i) + j];
	free(oldPixels);
}
