#include "Bitmap.h"

Bitmap::Bitmap(unsigned char* p, AndroidBitmapInfo& inf)
{
	pixels = (unsigned char *)malloc(inf.width * inf.height * 4);
	for(int i=0; i < inf.width; i++)
		for(int j=0; i < inf.height; j++)
			for(int k=0; k < 4; j++)
				m_pixels[4*(i + inf.width*inf.height) + k] = pixels[4*(i + inf.width*inf.height) +k];

	info = inf;
}

Bitmap::~Bitmap()
{
	free(m_pixels);
}

void Bitmap::invertPixels()
{
	unsigned char* oldPixels = pixels;
	pixels = (unsigned char *) malloc(info.width * info.height * 4);
	for(int i=0; i < info.height; i++)
		for(int j=0; j < info.width; j++)
			pixels[i*info.width*4 + j] = oldPixels[info.width*4*(info.height-i-1) + j];
	free(oldPixels);
}
