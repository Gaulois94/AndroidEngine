#include "Drawable.h"

ResourcesManager<Shader*> Drawable::shaders;

Drawable::Drawable(Shader* shader) : Transformable(), m_shader(shader), m_vboID(0), m_canDraw(true)
{
}

void Drawable::draw(Renderer* renderer)
{
	if(!m_canDraw)
		return;

	glUseProgram(m_shader->getProgramID());
	onDraw(renderer);
	glUseProgram(0);	
}

bool Drawable::canDraw() const
{
	return m_canDraw;
}

void Drawable::deleteVbos()
{
	if(glIsBuffer(m_vboID))
		glDeleteBuffers(1, &m_vboID);
}
