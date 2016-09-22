#include "Sprite.h"

Sprite::Sprite(Updatable* parent, Material* material, const Texture* texture) : Drawable(parent, material, Rectangle3f(0, 0, 0, 1, 1, 0)), m_subTextureRect(0.0f, 0.0f, 1.0f, 1.0f), m_texture(texture)
{
	float vertexCoords[] = {0.0f, 0.0f, 0.0f,
							1.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f,
						    1.0f, 1.0f, 0.0f
						   };

	float textureCoords[] = {0.0f, 0.0f,
							 1.0f, 0.0f,
							 0.0f, 1.0f,
							 1.0f, 1.0f
							};

	initVbos(vertexCoords, textureCoords);
}

void Sprite::onDraw(Render& render, const glm::mat4& mvp)
{
	if(!m_material)
		return;

	m_material->bindTexture(m_texture);
	m_material->init(render, mvp, getMatrix());
 	GLint vNormal = glGetAttribLocation(m_material->getShader()->getProgramID(), "vNormal");
	if(vNormal != -1)
	{
		glEnableVertexAttribArray(vNormal);
		float normal[] = {0.0, 0.0, 1.0};
		glVertexAttrib3fv(vNormal, normal);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		GLint vPosition     = glGetAttribLocation(m_material->getShader()->getProgramID(), "vPosition");
		GLint vTextureCoord = glGetAttribLocation(m_material->getShader()->getProgramID(), "vTextureCoord");

		GLint uMvp          = glGetUniformLocation(m_material->getShader()->getProgramID(), "uMVP");

		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, false, 3*sizeof(float), NULL);

		if(vTextureCoord != -1)
		{
			glEnableVertexAttribArray(vTextureCoord);
			glVertexAttribPointer(vTextureCoord, 2, GL_FLOAT, false, 2*sizeof(float), BUFFER_OFFSET(4 * sizeof(float) * 3));
		}

		glUniformMatrix4fv(uMvp, 1, false, glm::value_ptr(mvp));
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisableVertexAttribArray(vPosition);
		if(vTextureCoord != -1)
			glDisableVertexAttribArray(vTextureCoord);
		if(vNormal != -1)
			glDisableVertexAttribArray(vNormal);
	}	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_material->unbindTexture();
	m_material->disableShader();
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

void Sprite::initVbos(float* vertexCoords, float* textureCoords)
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
