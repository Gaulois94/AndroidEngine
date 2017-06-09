#include "Sprite.h"

Sprite::Sprite(Updatable* parent, Material* material, const Texture* texture) : Drawable(parent, material, Rectangle3f(0, 0, 0, 1, 1, 0)), m_subTextureRect(0.0f, 0.0f, 1.0f, 1.0f), m_texture(texture)
{
	const float vertexCoords[] = {0.0f, 0.0f, 0.0f,
							1.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f,
						    1.0f, 1.0f, 0.0f
						   };

	const float textureCoords[] = {0.0f, 0.0f,
							 1.0f, 0.0f,
							 0.0f, 1.0f,
							 1.0f, 1.0f
							};

	initVbos(vertexCoords, textureCoords);

	//Init the VAO
	genVertexArraysOES(1, &m_vao);
	bindVertexArrayOES(m_vao);
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		{
			glVertexAttribPointer(VPOSITION, 3, GL_FLOAT, false, 3*sizeof(float), NULL);
			glEnableVertexAttribArray(VPOSITION);

			glVertexAttribPointer(VTEXTURECOORD, 2, GL_FLOAT, false, 2*sizeof(float), BUFFER_OFFSET(4 * sizeof(float) * 3));
			glEnableVertexAttribArray(VTEXTURECOORD);
		}
	}
	bindVertexArrayOES(0);
}

Sprite::~Sprite()
{
	deleteVertexArraysOES(1, &m_vao);
}

void Sprite::onDraw(Render& render, const glm::mat4& mvp)
{
	if(!m_material)
		return;

	bindVertexArrayOES(m_vao);
	{
		m_material->bindTexture(m_texture);
		m_material->init(render, mvp, getMatrix());

		/*  
		GLint vNormal = glGetAttribLocation(m_material->getShader()->getProgramID(), "vNormal");
		if(vNormal != -1)
		{
			glEnableVertexAttribArray(vNormal);
			float normal[] = {0.0, 0.0, 1.0};
			glVertexAttrib3fv(vNormal, normal);
		}
		*/

		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		{
			GLint uMvp = glGetUniformLocation(m_material->getShader()->getProgramID(), "uMVP");
			glUniformMatrix4fv(uMvp, 1, false, glm::value_ptr(mvp));
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}	
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_material->unbindTexture();
	}
	bindVertexArrayOES(0);
}

void Sprite::setTexture(const Texture* texture, bool resetSubTextureRect)
{
	m_texture = texture;
	if(resetSubTextureRect)
		setSubTextureRect(FloatRect2(0.0f, 0.0f, 1.0f, 1.0f));
}

void Sprite::setSubTextureRect(const FloatRect2& subTextureRect)
{
	m_subTextureRect = subTextureRect;
	float textureCoords[] = {subTextureRect.x, subTextureRect.y,
							 subTextureRect.x + subTextureRect.width, subTextureRect.y,
							 subTextureRect.x, subTextureRect.y + subTextureRect.height,
							 subTextureRect.x + subTextureRect.width, subTextureRect.y + subTextureRect.height
							};

	int size = 4*sizeof(float);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		glBufferSubData(GL_ARRAY_BUFFER, 3*size, 2*size, textureCoords);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const Texture* Sprite::getTexture() const
{
	return m_texture;
}

const FloatRect2& Sprite::getSubTextureRect() const
{
	return m_subTextureRect;
}

void Sprite::initVbos(const float* vertexCoords, const float* textureCoords)
{
	deleteVbos();
	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		int size = 4 * sizeof(float);
		glBufferData(GL_ARRAY_BUFFER, 5*size, NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 3*size, vertexCoords);
		glBufferSubData(GL_ARRAY_BUFFER, 3*size, 2*size, textureCoords);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
