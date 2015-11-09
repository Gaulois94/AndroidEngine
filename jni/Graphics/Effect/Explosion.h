#ifndef DEF_EXPLOSION_INCLUDE
#define DEF_EXPLOSION_INCLUDE

#define GL_GLEXT_PROTOTYPES
#define GLM_FORCE_RADIANS

#include "Effect/Effect.h"
#include "Color.h"
#include "Materials/ExplosionMaterial.h"
#include "stdlib.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Explosion : public Effect
{
	public:
		Explosion(Updatable* parent, ExplosionMaterial* material, int nbParticles);
		~Explosion();

		void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
	private:
		Particle* m_particles;
		int m_nbParticles;
};

#endif
