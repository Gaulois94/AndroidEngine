#include "Text.h"

short Text::drawOrder[6] = {0, 1, 2, 0, 2, 3};

Text::Text(Font* font, const char* text, const Color& color) : Drawable(Drawable::shaders.get("text")), m_letterCoords(NULL), m_textureCoords(NULL), m_font(font), m_text(NULL), m_color(color)
{
	setText(text);
}

Text::Text() : Drawable(Drawable::shaders.get("text")), m_letterCoords(0), m_textureCoords(0), m_font(0), m_text(0), m_color()
{
}

Text::~Text()
{
	deleteVbos();
	if(m_letterCoords != NULL)
	{
		free(m_letterCoords);
		free(m_textureCoords);
		free(m_text);
	}
}

void Text::setFont(Font* font)
{
	m_font = font;
	setText(m_text);
}

void Text::setText(const char* text)
{
	if(m_letterCoords != NULL)
	{
		free(m_letterCoords);
		free(m_textureCoords);
		free(m_text);
	}

	m_textureCoords = (float*) malloc(strlen(text) * 4 * 2 * sizeof(float));
	m_letterCoords = (float*) malloc(strlen(text) * 4 * 3 * sizeof(float));

	m_text = (char*) malloc(strlen(text)*sizeof(char));
	strcpy(m_text, text);
	float posX = 0.0f;
	float posY = 0.0f;

	for(int i=0; i < strlen(text); i++)
	{
		if(text[i] == CHAR_NL)
		{
			LOG_ERROR("OK");
			posX = 0;
			posY -= (float) m_font->getLineHeight() / 200.0f;

			for(int j =0; j < 4; j++)
			{
				for(int k=0; k < 2; k++)
					m_textureCoords[i*4*2 + j*2 + k] = 0.0f;

				for(int k=0; k < 3; k++)
					m_letterCoords[i*4*3 + j*3 + k] = 0.0f;
			}

			continue;
		}

		glm::vec2 pos = m_font->getPosition(text[i]);
		glm::vec2 size = m_font->getSize(text[i]);
		FloatRect2 rectTexture = m_font->getTexture()->getRect(pos, size);

		size = size/200.0f;

		float rectTextureCoord[] = {rectTexture.x, rectTexture.y,
									rectTexture.x + rectTexture.width, rectTexture.y,
									rectTexture.x + rectTexture.width, rectTexture.y + rectTexture.height,
									rectTexture.x, rectTexture.y + rectTexture.height};

		float rectLetterCoord[]  = {posX, posY - size.y, 0,
									posX + size.x, posY - size.y, 0,
									posX + size.x, posY, 0,
									posX, posY, 0};

		for(int j =0; j < 4; j++)
		{
			for(int k=0; k < 2; k++)
				m_textureCoords[i*4*2 + j*2 + k] = rectTextureCoord[j*2 + k];

			for(int k=0; k < 3; k++)
				m_letterCoords[i*4*3 + j*3 + k] = rectLetterCoord[j*3 + k];
		}
		posX += size.x;
	}

	initVbos();
}

void Text::onDraw(Renderer* renderer)
{
	if(m_font == NULL || m_text == NULL)
		return;

	glm::mat4 mvp(1.0f);

	glBindTexture(GL_TEXTURE_2D, m_font->getTexture()->getID());
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{

		GLuint vPosition      = glGetAttribLocation(m_shader->getProgramID(), "vPosition");
		GLuint vTextureCoord  = glGetAttribLocation(m_shader->getProgramID(), "vTextureCoord");
		glEnableVertexAttribArray(vPosition);
		glEnableVertexAttribArray(vTextureCoord);

		GLuint uTextureHandle = glGetUniformLocation(m_shader->getProgramID(), "uTexture");
		GLuint uColor         = glGetUniformLocation(m_shader->getProgramID(), "uColor");
		GLuint uMvp           = glGetUniformLocation(m_shader->getProgramID(), "uMVP");

		float color[] = {m_color.r, m_color.g, m_color.b, m_color.a};
		glUniform1i(uTextureHandle, 0);
		glUniform4fv(uColor, 1, color);
		glUniformMatrix4fv(uMvp, 1, false, glm::value_ptr(mvp));

		for(int i=0; i < strlen(m_text); i++)
		{
			glVertexAttribPointer(vPosition, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(i*4*3 * sizeof(float)));
			glVertexAttribPointer(vTextureCoord, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(4 * 3 * sizeof(float) * strlen(m_text) + i*2*4*sizeof(float)));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, Text::drawOrder);
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::setColor(const Color& color)
{
	m_color = color;
}

const Font* Text::getFont()
{
	return m_font;
}

const char* Text::getText()
{
	return m_text;
}

const Color& Text::getColor()
{
	return m_color;
}

void Text::initVbos()
{
	deleteVbos();
	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		int size = 4 * sizeof(float) * strlen(m_text);
		//3 for letterCoord and 2 for textureCoord
		glBufferData(GL_ARRAY_BUFFER, (3 + 2) * size, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 3*size, m_letterCoords);
		glBufferSubData(GL_ARRAY_BUFFER, 3*size, 2*size, m_textureCoords);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
