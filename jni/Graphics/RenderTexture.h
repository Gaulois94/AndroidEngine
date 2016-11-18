#ifndef  RENDERTEXTURE_INC
#define  RENDERTEXTURE_INC

#define GL_GLEXT_PROTOTYPES

#include "Render.h"
#include "Texture.h"
#include "Vector2.h"
#include "GLES2/gl2ext.h"

class RenderTexture : public Render
{
	public:
		RenderTexture(Updatable* parent, const Vector2ui& size);
		~RenderTexture();

		void display();
		void initDraw();
		void stopDraw();
		void clear();

		const Texture* getTexture() const;
	private:
		GLuint m_frameBuffer;
		Texture* m_texture;
};

#endif
