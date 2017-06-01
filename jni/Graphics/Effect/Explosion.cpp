#include "Effect/Explosion.h"
#include "logger.h"

Explosion::Explosion(Updatable* parent, ExplosionMaterial* material, int nbParticles) : Effect(parent, material), m_particles(NULL), m_nbParticles(nbParticles)
{
	srand(time(NULL));
	m_particles = (Particle*)malloc(sizeof(Particle)*nbParticles);
	for(int i=0; i < nbParticles; i++)
	{
		float radius[]                   = {rand() / (float) RAND_MAX*0.25f,
											rand() / (float) RAND_MAX*0.25f,
											rand() / (float) RAND_MAX*0.25f/5.0f
										   };

		float phi                        = rand() / (float) RAND_MAX*2*3.14 - 3.14;
		float theta                      = rand() / (float) RAND_MAX*3.14 - 3.14/2;

		m_particles[i].pos[0]            = radius[0] * (float) cos(theta) * (float) cos(phi);
		m_particles[i].pos[1]            = radius[2] * (float) sin(theta);
		m_particles[i].pos[2]            = radius[1] * (float) cos(theta) * (float) sin(phi);

		m_particles[i].life              = 150 + rand()%20 - 30*glm::length(glm::vec3(radius[0], radius[1], radius[2])); //Maximum 70 iterations
		for(int j=0; j < 3; j++)
		{
			float signe = 1.0;
			if(m_particles[i].pos[j] < 0.0f)
				signe = -1.0;
			m_particles[i].speed[j] = signe * radius[j] * (float)(rand()) / RAND_MAX * 0.04;
			if(j==1)
				m_particles[i].speed[j] *=  (float) (0.25  + sin(radius[0]*3.14/0.25));
		}
	}
}

Explosion::~Explosion()
{
	free(m_particles);
}

void Explosion::onDraw(Render& render, const glm::mat4& mvp)
{
	if(!m_material)
		return;

	//initialize the material
	m_material->init(render, mvp, getMatrix());

	//get locations
	GLint vPosition  = glGetAttribLocation(m_material->getShader()->getProgramID(), "vPosition");
	GLint uMvp       = glGetUniformLocation(m_material->getShader()->getProgramID(), "uMVP");
	GLint uIntensity = glGetUniformLocation(m_material->getShader()->getProgramID(), "uIntensity");

	for(int i=0; i < m_nbParticles; i++)
	{
		if(m_particles[i].life == 0)
			continue;

		m_particles[i].life--;

		//update the pos
		for(int j=0; j < 3; j++)
			m_particles[i].pos[j] = m_particles[i].pos[j] + m_particles[i].speed[j];

		glEnableVertexAttribArray(vPosition);

		glVertexAttribPointer(vPosition, 3, GL_FLOAT, false, 0, m_particles[i].pos);
		glUniformMatrix4fv(uMvp, 1, false, glm::value_ptr(mvp));
		glUniform1f(uIntensity, 30.0f/m_particles[i].life);

		glDrawArrays(GL_POINTS, 0, 1);
	}
}
