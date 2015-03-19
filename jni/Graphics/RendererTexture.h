#ifndef DEF_RENDERERTEXTURE_INCLUDE
#define DEF_RENDERERTEXTURE_INCLUDE

#include "Texture.h"
#include <GLES2/gl2.h>

class RendererTexture
{
	public:
		RendererTexture(int width, int height);
	private:
		Texture  m_texture;
		GLuint   m_framebuffer;
};

#endif
