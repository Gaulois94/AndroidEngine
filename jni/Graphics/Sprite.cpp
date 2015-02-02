#include "Sprite.h"

short Sprite::drawOrder[6] = {0, 1, 2, 0, 2, 3};

Sprite::Sprite(const Texture* texture) : Drawable(Drawable::shaders.get("texture")), m_subTextureRect(0.0f, 0.0f, 1.0f, 1.0f), m_texture(texture)
{
	float vertexCoords[] = {0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 0.0f,
							1.0f, 0.0f, 0.0f,
						    1.0f, 1.0f, 0.0f
						   };

	float textureCoords[] = {0.0f, 1.0f,
							 0.0f, 0.0f,
							 1.0f, 0.0f,
							 1.0f, 1.0f
							};

	initVbos(vertexCoords, textureCoords);
}

void Sprite::onDraw(Renderer* renderer, glm::mat4& mvp)
{
	glBindTexture(GL_TEXTURE_2D, m_texture->getID());
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		GLuint vPosition     = glGetAttribLocation(m_shader->getProgramID(), "vPosition");
		GLuint vTextureCoord = glGetAttribLocation(m_shader->getProgramID(), "vTextureCoord");

		GLuint uMvp          = glGetUniformLocation(m_shader->getProgramID(), "uMVP");
		GLuint uTextureHandle = glGetUniformLocation(m_shader->getProgramID(), "uTexture");

		glEnableVertexAttribArray(vPosition);
		glEnableVertexAttribArray(vTextureCoord);

		glVertexAttribPointer(vPosition, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(vTextureCoord, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(4 * sizeof(float) * 3));

		glUniformMatrix4fv(uMvp, 1, false, glm::value_ptr(mvp));
		glUniform1i(uTextureHandle, 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, Sprite::drawOrder);
	}	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
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
	float textureCoords[] = {subTextureRect.x, subTextureRect.y + subTextureRect.height,
							 subTextureRect.x, subTextureRect.y,
							 subTextureRect.x + subTextureRect.width, subTextureRect.y,
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
