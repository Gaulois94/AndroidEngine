#ifndef DEF_EFFECT_INCLUDE
#define DEF_EFFECT_INCLUDE

#define GL_GLEXT_PROTOTYPES
#define GLM_FORCE_RADIANS

#include "Drawable.h"
#include <cmath>
#include "Color.h"
#include "Materials/ExplosionMaterial.h"
#include "stdlib.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Particle
{
	float pos[3];
	short life;
	float intensity;
	float speed[3];
};

class Effect : public Drawable
{
	public:
		Effect(ExplosionMaterial* material);
	private:
		Particle* m_particles;
};

#endif
