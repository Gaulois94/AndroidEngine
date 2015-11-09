#ifndef DEF_EXPLOSIONMATERIAL_INCLUDE
#define DEF_EXPLOSIONMATERIAL_INCLUDE

#include "Materials/EffectMaterial.h"

class ExplosionMaterial : public EffectMaterial
{
	public:
		ExplosionMaterial(const Color& baseColor = Color::WHITE);
		void init(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
	private:
		float m_color[4];
};

#endif
