#ifndef DEF_TEXTUREMATERIAL_INCLUDE
#define DEF_TEXTUREMATERIAL_INCLUDE

#include "Materials/Material.h"

//Basic texture material : show the texture without doing calcul on its pixels.
//Remember to bind the texture before using it
class TextureMaterial : public Material
{
	public:
		TextureMaterial();
};

#endif
