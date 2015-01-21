#include "Shape/TriangleShape.h"

TriangleShape::TriangleShape(const glm::vec3* vertexCoords, int nbVertex, const Color* colors, bool uniColor, GLuint mode) : Drawable(Drawable::shaders.get("colorshader")), m_nbVertex(nbVertex), m_useUniColor(uniColor), m_mode(mode)
{
	m_uniColor = (float*)malloc(4*sizeof(float));
	for(int i=0; i < 4; i++)
		m_uniColor[i] = 0.0f;
	setDatas(vertexCoords, colors, nbVertex, uniColor);
}

TriangleShape::TriangleShape(const float* vertexCoords, int nbVertex, const float* colors, bool uniColor, GLuint mode) : Drawable(Drawable::shaders.get("colorshader")), m_nbVertex(nbVertex), m_useUniColor(uniColor), m_mode(mode)
{
	m_uniColor = (float*)malloc(4*sizeof(float));
	for(int i=0; i < 4; i++)
		m_uniColor[i] = 0.0f;
	setDatas(vertexCoords, colors, nbVertex, uniColor);
}

TriangleShape::~TriangleShape()
{
	Drawable::~Drawable();
	free(m_uniColor);
}

void TriangleShape::onDraw(Renderer* renderer, glm::mat4& mvp)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		GLuint vPosition = glGetAttribLocation(m_shader->getProgramID(), "vPosition");
		GLuint vColor    = glGetAttribLocation(m_shader->getProgramID(), "vColor");

		GLuint uMvp      = glGetUniformLocation(m_shader->getProgramID(), "uMVP");
		GLuint uUseColor = glGetUniformLocation(m_shader->getProgramID(), "uUseColor");

		glEnableVertexAttribArray(vPosition);
		glEnableVertexAttribArray(vColor);

		glVertexAttribPointer(vPosition, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(vColor, 4, GL_FLOAT, false, 0, BUFFER_OFFSET(m_nbVertex * 3*sizeof(float)));
		if(m_uniColor)
		{
			GLuint uColor    = glGetUniformLocation(m_shader->getProgramID(), "uColor");
			glUniform4fv(uColor, 1, m_uniColor);
		}
		glUniformMatrix4fv(uMvp, 1, false, glm::value_ptr(mvp));
		glUniform1i(uUseColor, m_useUniColor);
		glDrawArrays(m_mode, 0, m_nbVertex);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TriangleShape::setDatas(const glm::vec3* vertexCoords, const Color* colors, int nbVertex, bool uniColor)
{
	m_nbVertex = nbVertex;
	m_useUniColor = uniColor;

	int size = m_nbVertex * sizeof(float) * (3+4);

	deleteVbos();
	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	setVertexCoord(vertexCoords);
	if(uniColor == false && colors != NULL)
		setColors(colors);
	else if(colors != NULL)
		setUniColor(colors[0]);
}

void TriangleShape::setDatas(const float* vertexCoords, const float* colors, int nbVertex, bool uniColor)
{
	m_nbVertex = nbVertex;
	m_useUniColor = uniColor;

	if(uniColor && colors != NULL)
		for(int i=0; i < 4; i++)
			m_uniColor[i] = colors[i];

	initVbos(vertexCoords, colors);
}

void TriangleShape::setVertexCoord(const glm::vec3* vertexCoord)
{
	float* v=(float*)malloc(3*m_nbVertex*sizeof(float));
	if(vertexCoord == NULL)
		for(int i=0; i < 3*m_nbVertex; i++)
			v[i] = 0.0f;

	else
		for(int i=0; i < m_nbVertex; i++)
			for(int j=0; j < 3; j++)
				v[3*i+j] = vertexCoord[i][j];
	setArrayVertex(v);
	free(v);
}

void TriangleShape::setColors(const Color* colors)
{
	float* c = (float*)malloc(4*m_nbVertex*sizeof(float));
	if(colors != NULL)
		for(int i=0; i < m_nbVertex; i++)
			colors[i].getFloatArray(&(c[4*i]));
	else
		for(int i=0; i < m_nbVertex; i++)
			for(int j=0; j < 4; j++)
				c[4*i + j] = 0.0f;

	setArrayColor(c);
	free(c);
}

void TriangleShape::setUniColor(const Color& color)
{
	color.getFloatArray(m_uniColor);
}

void TriangleShape::useUniColor(bool uniColor)
{
	m_useUniColor = uniColor;
}

bool TriangleShape::isUsingUniColor()
{
	return m_uniColor;
}

Color TriangleShape::getUniColor()
{
	Color c;

	c.r = m_uniColor[0];
	c.g = m_uniColor[1];
	c.b = m_uniColor[2];
	c.a = m_uniColor[3];

	return c;
}

int TriangleShape::getNbVertex()
{
	return m_nbVertex;
}

Color TriangleShape::getColor(int vertex)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	//m_nbVertex*3 are the offset of colors on the buffer
	float *colors = (float*) glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES) + (m_nbVertex*3);

	Color c(colors[4*vertex], colors[4*vertex + 1], colors[4*vertex + 2], colors[4*vertex + 3]);
	glUnmapBufferOES(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return c;
}

glm::vec3 TriangleShape::getPosition(int vertex)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	float* position = (float*) glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);

	glm::vec3 v(position[3*vertex], position[3*vertex + 1], position[3*vertex + 2]);
	glUnmapBufferOES(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return v;
}

void TriangleShape::initVbos(const float* vertexCoord, const float* colors)
{
	int size = m_nbVertex * sizeof(float) * (3+4);
	deleteVbos();
	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	setArrayVertex(vertexCoord);
	if(!m_useUniColor)
		setArrayColor(colors);
}

void TriangleShape::setArrayVertex(const float* vertexCoords)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, 3*m_nbVertex*sizeof(float), vertexCoords);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TriangleShape::setArrayColor(const float* colors)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		glBufferSubData(GL_ARRAY_BUFFER, 3*m_nbVertex*sizeof(float), 4*m_nbVertex*sizeof(float), colors);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
