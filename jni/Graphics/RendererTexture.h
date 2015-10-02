#ifndef DEF_RENDERERTEXTURE_INCLUDE
#define DEF_RENDERERTEXTURE_INCLUDE

#include "Texture.h"
#include <GLES2/gl2.h>

class RendererTexture : public Renderer
{
	public:
		RendererTexture(int width, int height);
		~RendererTexture();
		
		void initDraw();
		void stopDraw();
		void clear();

		const Texture* getTexture();
	private:
		Texture* m_texture;
		GLuint m_framebufferID;
};

#endif
