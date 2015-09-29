#ifndef DEF_EFFECTMATERIAL_INCLUDE
#define DEF_EFFECTMATERIAL_INCLUDE

#include "Materials/Material.h"
#include "Shader.h"

/** \brief basic class for effect materials */
class EffectMaterial : public Material
{
	public:
		/** \brief the basic constructor of the material. Do nothing except call its mother constructor
		 * \param shader the shader of this material.*/
		EffectMaterial(Shader* shader);
};

#endif
