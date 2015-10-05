#include "ColorMaterial.h"

ColorMaterial::ColorMaterial(const Color* color, int nbVertex) : Material(Shader::shaders.get("color"))
{
	setColor(color, nbVertex);
}

ColorMaterial::ColorMaterial(const float* color, int nbVertex) : Material(Shader::shaders.get("color"))
{
	setColor(color, nbVertex);
}

void ColorMaterial::init(Render& render, const glm::mat4& mvp)
{
	Material::init(render, mvp);
	GLint vColor    = glGetAttribLocation(m_shader->getProgramID(), "vColor");
	GLint uUseColor = glGetUniformLocation(m_shader->getProgramID(), "uUseColor");

	glEnableVertexAttribArray(vColor);
	glUniform1i(uUseColor, false);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, false, 0, NULL);
}

void ColorMaterial::setColor(const Color* color, int nbVertex)
{
	float* c = (float*) malloc(nbVertex * 4 * sizeof(float));
	for(int i=0; i < nbVertex; i++)
		color[i].getFloatArray(&(c[4*i]));

	setColor(c, nbVertex);
	free(c);
}

void ColorMaterial::setColor(const float* color, int nbVertex)
{
	m_nbVertex = nbVertex;
	deleteVbos();
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		glBufferData(GL_ARRAY_BUFFER, 4*sizeof(float)*nbVertex, color, GL_DYNAMIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Color* ColorMaterial::getColor() const
{
	Color* c = (Color*)malloc(m_nbVertex*4*sizeof(float));
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		float *colors = (float*) glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);

		for(int i=0; i < m_nbVertex; i++)
			c[i] = Color(&(colors[4*i]));

		glUnmapBufferOES(GL_ARRAY_BUFFER);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return c;
}

Color ColorMaterial::getColor(int vertex) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	float *colors = (float*) glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);

	Color c(&(colors[4*vertex]));
	glUnmapBufferOES(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return c;
}

int ColorMaterial::getNbVertex() const
{
	return m_nbVertex;
}
