#ifndef TEXTURE_INCLUDE
#define TEXTURE_INCLUDE

#include <iostream>
#include "Bitmap.h"

class Texture
{
	public:
		Texture(int width, int height);
		Texture(float[] pixels, int width, int height, bool alpha=true);
		Texture(const Bitmap* bitmap);
		~Texture();

		int getID();
		int getWidth();
		int getHeight();
	private:
		int m_width;
		int m_height;
		int m_id;
};

#endif
