#ifndef  RENDERTEXTURE_INC
#define  RENDERTEXTURE_INC

#include "Render.h"
#include "Sprite.h"

class RenderTexture : public Render
{
	public:
		RenderTexture(Updatable* parent, const Vector2f& size);

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
