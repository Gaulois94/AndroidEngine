#include "Shape/TriangleShape.h"

TriangleShape::TriangleShape(Updatable* parent, Material* material, const glm::vec3* vertexCoords, const glm::vec3* normalCoords, uint32_t nbVertex, GLuint mode) : Drawable(parent, material), m_nbVertex(nbVertex), m_mode(mode), m_drawOrderVboID(0), m_drawOrderLength(0)
{
	if(normalCoords)
		setDatas(vertexCoords, normalCoords, nbVertex);
	else
	{
		float* nc = makeNormalCoords(mode, vertexCoords, nbVertex);
		float* vc = convertGlm3ToFloat(vertexCoords, nbVertex);
		setDatas(vc, nc, nbVertex);

		free(vc);
		free(nc);
	}
}

TriangleShape::TriangleShape(Updatable* parent, Material* material, const float* vertexCoords, const float* normalCoords, uint32_t nbVertex, GLuint mode) : Drawable(parent, material), m_nbVertex(nbVertex), m_mode(mode), m_drawOrderVboID(0), m_drawOrderLength(0)
{
	if(normalCoords)
		setDatas(vertexCoords, normalCoords, nbVertex);
	else
	{
		float* nc = makeNormalCoords(mode, vertexCoords, nbVertex);
		setDatas(vertexCoords, nc, nbVertex);
		free(nc);
	}
}

void TriangleShape::onDraw(Render& render, const glm::mat4& mvp)
{
	if(!m_material)
		return;

	if(!glIsBuffer(m_vboID))
		return;

	m_material->init(render, mvp);
	LOG_ERROR("END MATERIAL INIT");
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		GLint vPosition         = glGetAttribLocation(m_material->getShader()->getProgramID(), "vPosition");
		GLint vNormal           = glGetAttribLocation(m_material->getShader()->getProgramID(), "vNormal");
		GLint uMvp              = glGetUniformLocation(m_material->getShader()->getProgramID(), "uMVP");

		glEnableVertexAttribArray(vPosition);

		glVertexAttribPointer(vPosition, 3, GL_FLOAT, false, 3*sizeof(float), BUFFER_OFFSET(0));
		if(vNormal != -1)
		{
			glEnableVertexAttribArray(vNormal);
			glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, 3*sizeof(float), BUFFER_OFFSET(sizeof(float)*3*m_nbVertex));
		}
		glUniformMatrix4fv(uMvp, 1, false, glm::value_ptr(mvp));

		if(glIsBuffer(m_drawOrderVboID))
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_drawOrderVboID);
				glDrawElements(m_mode, m_drawOrderLength, GL_UNSIGNED_INT, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		else
			glDrawArrays(m_mode, 0, m_nbVertex);

		glDisableVertexAttribArray(vPosition);
		if(vNormal != -1)
			glDisableVertexAttribArray(vNormal);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	LOG_ERROR("END ON DRAW TRIANGLE SHAPE");
}

void TriangleShape::setDatas(const glm::vec3* vertexCoords, const glm::vec3* normalCoords, uint32_t nbVertex)
{
	m_nbVertex = nbVertex;

	uint32_t size = sizeof(float) * (m_nbVertex * 3*2);

	Drawable::deleteVbos();
	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	setVertexCoord(vertexCoords);
	if(normalCoords)
		setNormalCoord(normalCoords);
	else
	{
		float* nc = makeNormalCoords(m_mode, vertexCoords, nbVertex);
		if(nc)
		{
			setArrayNormal(nc);
			free(nc);
		}
		else
			LOG_ERROR("Can't create normals for the mode %d", m_mode);
	}
}

void TriangleShape::setDatas(const float* vertexCoords, const float* normalCoords, uint32_t nbVertex)
{
	m_nbVertex = nbVertex;
	if(normalCoords)
		initVbos(vertexCoords, normalCoords);
	else
	{
		float* nc = makeNormalCoords(m_mode, vertexCoords, nbVertex);
		if(nc==NULL)
			LOG_ERROR("Can't create normals for the mode %d", m_mode);
		initVbos(vertexCoords, nc);
		if(nc != NULL)
			free(nc);
	}
}

void TriangleShape::setVertexCoord(const glm::vec3* vertexCoords)
{
	float* v=convertGlm3ToFloat(vertexCoords, m_nbVertex);
	setArrayVertex(v);
	free(v);
}

void TriangleShape::setNormalCoord(const glm::vec3* normalCoords)
{
	float* n=convertGlm3ToFloat(normalCoords, m_nbVertex);
	setArrayNormal(n);
	free(n);
}

uint32_t TriangleShape::getNbVertex()
{
	return m_nbVertex;
}

glm::vec3 TriangleShape::getPositionVertex(uint32_t vertex)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	float* position = (float*) glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);

	glm::vec3 v(position[3*vertex], position[3*vertex + 1], position[3*vertex + 2]);
	glUnmapBufferOES(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return v;
}

void TriangleShape::initVbos(const float* vertexCoords, const float* normalCoords)
{
	uint32_t size = (m_nbVertex * 3 * 2) * sizeof(float);
	Drawable::deleteVbos();
	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	setArrayVertex(vertexCoords);
	if(normalCoords)
		setArrayNormal(normalCoords);
	else
	{
		float* nc = makeNormalCoords(m_mode, vertexCoords, m_nbVertex);
		if(nc == NULL)
			LOG_ERROR("Can't create normals for the mode %d", m_mode);
		else
		{
			setArrayNormal(nc);
			free(nc);
		}
	}
}

void TriangleShape::setArrayVertex(const float* vertexCoords)
{
	//We recompile the default size and position of the triangleShape
	glm::vec3 defaultPositionMin;
	glm::vec3 defaultPositionMax;

	//The if(i < 3) is if we haven't initialized the default position yet
	for(uint32_t i=0; i < m_nbVertex*COORD_PER_TRIANGLES; i++)
	{
		//The x coords
		if(i%3 == 0)
		{
			if(i<3)
				defaultPositionMin.x = defaultPositionMax.x = vertexCoords[i];
			else if(vertexCoords[i] > defaultPositionMax.x)
				defaultPositionMax.x = vertexCoords[i];
			else if(vertexCoords[i] < defaultPositionMin.x)
				defaultPositionMin.x = vertexCoords[i];
		}

		//The y coords
		else if(i%3 == 1)
		{
			if(i<3)
				defaultPositionMin.y = defaultPositionMax.y = vertexCoords[i];
			else if(vertexCoords[i] > defaultPositionMax.y)
				defaultPositionMax.y = vertexCoords[i];
			else if(vertexCoords[i] < defaultPositionMin.y)
				defaultPositionMin.y = vertexCoords[i];
		}

		//The z coords
		else if(i%3 == 2)
		{
			if(i<3)
				defaultPositionMin.z = defaultPositionMax.z = vertexCoords[i];
			else if(vertexCoords[i] > defaultPositionMax.z)
				defaultPositionMax.z = vertexCoords[i];
			else if(vertexCoords[i] < defaultPositionMin.z)
				defaultPositionMin.z = vertexCoords[i];
		}
	}
	setDefaultPos(defaultPositionMin);
	setDefaultSize(defaultPositionMax-defaultPositionMin);

	//Then we store the vertex coords to the buffer
	if(glIsBuffer(m_vboID))
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
			glBufferSubData(GL_ARRAY_BUFFER, 0, COORD_PER_TRIANGLES*m_nbVertex*sizeof(float), vertexCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void TriangleShape::setArrayNormal(const float* normalCoords)
{
	if(glIsBuffer(m_vboID))
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
			glBufferSubData(GL_ARRAY_BUFFER, COORD_PER_TRIANGLES*m_nbVertex*sizeof(float), COORD_PER_TRIANGLES*m_nbVertex*sizeof(float), normalCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void TriangleShape::setDrawOrder(const uint32_t* drawOrder, uint32_t size)
{
	deleteDrawOrder();
	if(drawOrder == NULL)
	{
		m_drawOrderLength = 0;
		return;
	}
	
	glGenBuffers(1, &m_drawOrderVboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_drawOrderVboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(uint32_t), drawOrder, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_drawOrderLength = size;
}

bool TriangleShape::useDrawOrder()
{
	return glIsBuffer(m_drawOrderVboID);
}

void TriangleShape::deleteVbos()
{
	Drawable::deleteVbos();
	deleteDrawOrder();
}

void TriangleShape::deleteDrawOrder()
{
	if(glIsBuffer(m_drawOrderVboID))
		glDeleteBuffers(1, &m_drawOrderVboID);
}

float* makeNormalCoords(GLuint mode, const glm::vec3* vertexCoords, uint32_t nbVertex)
{
	float* normalCoords=NULL;

	if(mode==GL_TRIANGLES)
	{
		float* normalCoords = (float*)malloc(COORD_PER_TRIANGLES*nbVertex * sizeof(float));
		for(uint32_t i=0; i < nbVertex/3; i++)
		{
			glm::vec3 c = glm::normalize(glm::cross(vertexCoords[i*3+1] - vertexCoords[i*3], 
													vertexCoords[i*3+2] - vertexCoords[i*3]));

			//Because 1 normal per vertex
			for(uint32_t j=0; j < 3; j++)
				for(uint32_t k=0; k < 3; k++)
					normalCoords[i*9+j*3+k] = c[k];
		}
	}

	else if(mode==GL_TRIANGLE_FAN)
	{
		float* normalCoords = (float*)malloc(COORD_PER_TRIANGLES*nbVertex * sizeof(float));
		for(uint32_t i=0; i < nbVertex/3; i++)
		{
			glm::vec3 c = glm::normalize(glm::cross(vertexCoords[0] - vertexCoords[i], 
													vertexCoords[0] - vertexCoords[i+1]));

			//Because 1 normal per vertex
			for(uint32_t j=0; j < 3; j++)
				for(uint32_t k=0; k < 3; k++)
					normalCoords[i*9+j*3+k] = c[k];
		}
	}
	return normalCoords;
}

float* makeNormalCoords(GLuint mode, const float* vertexCoords, uint32_t nbVertex)
{
	glm::vec3* vc = convertFloatToGlm3(vertexCoords, nbVertex);
	float* normalCoords = makeNormalCoords(mode, vc, nbVertex);
	free(vc);
	return normalCoords;
}

glm::vec3* convertFloatToGlm3(const float* vertexCoords, uint32_t nbVertex)
{
	glm::vec3* vc = (glm::vec3*)malloc(sizeof(glm::vec3) * nbVertex);
	if(vertexCoords)
		for(uint32_t i=0; i < nbVertex; i++)
			for(uint32_t j=0; j < 3; j++)
				vc[i][j] = vertexCoords[i*3+j];
	else
		for(uint32_t i=0; i < nbVertex; i++)
			for(uint32_t j=0; j < 3; j++)
				vc[i][j] = 0.0f;
	return vc;
}

float* convertGlm3ToFloat(const glm::vec3* vertexCoords, uint32_t nbVertex)
{
	float* vc = (float*)malloc(3*nbVertex*sizeof(float));
	if(vertexCoords)
		for(uint32_t i=0; i < nbVertex; i++)
			for(uint32_t j=0; j < 3; j++)
				vc[i*3+j] = vertexCoords[i][j];
	else
		for(uint32_t i=0; i < nbVertex; i++)
			for(uint32_t j=0; j < 3; j++)
				vc[i*3+j] = 0.0f;

	return vc;
}
