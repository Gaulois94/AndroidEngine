#ifndef DEF_EFFECTMATERIAL_INCLUDE
#define DEF_EFFECTMATERIAL_INCLUDE

#include "Materials/Material.h"
#include "Shader.h"

class EffectMaterial : public Material
{
	public:
		EffectMaterial(Shader* shader);
};

#endif
