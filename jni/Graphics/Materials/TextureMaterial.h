#ifndef DEF_TEXTUREMATERIAL_INCLUDE
#define DEF_TEXTUREMATERIAL_INCLUDE

#include "Materials/Material.h"

enum TextureColor
{
	TEXTURE_RGBA,
	TEXTURE_B_AND_W
};

//Basic texture material : show the texture without doing calcul on its pixels.
//Remember to bind the texture before using it
class TextureMaterial : public Material
{
	public:
		TextureMaterial();
		void init(Render& render, const glm::mat4& mvp, const glm::mat4& modelMatrix);
		void setColorMode(TextureColor c) {m_colorMode = c;}
	private:
		void getAttributs();

		TextureColor m_colorMode = TEXTURE_RGBA;
		GLint m_uType;
};

#endif
