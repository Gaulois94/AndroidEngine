#include "Text.h"

Text::Text(Updatable* parent, Material* material, Font* font, const char* text) : Drawable(parent, material), m_font(font), m_text(NULL)
{
	setText(text);
}

Text::Text() : Drawable(NULL, NULL), m_font(0), m_text(0)
{
}

Text::~Text()
{
	if(m_text)
		free(m_text);
}

void Text::setFont(Font* font)
{
	m_font = font;
	setText(m_text);
}

void Text::setText(const char* text)
{
	if(text != m_text)
	{
		if(m_text != NULL)
			free(m_text);

		//We copy the new text and store it
		m_text = (char*) malloc((strlen(text)+1)*sizeof(char));
		strcpy(m_text, text);

		if(!m_font || !text)
		{
			setDefaultSize(glm::vec3(0.0f, 0.0f, 0.0f));//No text, no size
			return;
		}
	}

	//A text is just a number of letter drawn one by one
	float *textureCoords = (float*) malloc(strlen(text) * 4 * 2 * sizeof(float));
	float *letterCoords = (float*) malloc(strlen(text) * 4 * 3 * sizeof(float));

	//We start at the position (0.0, 0.0)
	float posX = 0.0f;
	float posY = 0.0f;

	for(unsigned int i=0; i < strlen(text); i++)
	{
		//If the character is \n, we jump to the next line (posY -= m_font->getLineHeight())
		if(text[i] == CHAR_NL)
		{
			posX = 0;
			posY -= (float) m_font->getLineHeight() / 200.0f;

			for(int j =0; j < 4; j++)
			{
				for(int k=0; k < 2; k++)
					textureCoords[i*4*2 + j*2 + k] = 0.0f;

				for(int k=0; k < 3; k++)
					letterCoords[i*4*3 + j*3 + k] = 0.0f;
			}

			continue;
		}

		FloatRect2 rectTexture = m_font->getTexture()->getDirectXRect(m_font->getCharRect(m_text[i]));

		glm::vec2 size = m_font->getSize(m_text[i])/200.f;

		float rectTextureCoord[] = {rectTexture.x, rectTexture.y,
									rectTexture.x + rectTexture.width, rectTexture.y,
									rectTexture.x, rectTexture.y + rectTexture.height,
									rectTexture.x + rectTexture.width, rectTexture.y + rectTexture.height};

		float rectLetterCoord[]  = {posX, posY, 0,
									posX + size.x, posY, 0,
									posX, posY + size.y, 0,
									posX + size.x, posY + size.y, 0};

		for(int j =0; j < 4; j++)
		{
			for(int k=0; k < 2; k++)
				textureCoords[i*4*2 + j*2 + k] = rectTextureCoord[j*2 + k];

			for(int k=0; k < 3; k++)
				letterCoords[i*4*3 + j*3 + k] = rectLetterCoord[j*3 + k];
		}
		posX += size.x;
	}

	initVbos(letterCoords, textureCoords);
	setDefaultSize(glm::vec3(posX, -posY + m_font->getLineHeight()/200.f, 0.0f));//We readjust the default size of the text
	free(letterCoords);
	free(textureCoords);
}

void Text::onDraw(Render& render, const glm::mat4& mvp)
{
	if(m_font == NULL || m_text == NULL || m_material == NULL || !glIsBuffer(m_vboID))
		return;

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	m_material->bindTexture(m_font->getTexture());
	m_material->init(render, mvp);
	{
		GLint vPosition      = glGetAttribLocation(m_material->getShader()->getProgramID(), "vPosition");
		GLint vTextureCoord  = glGetAttribLocation(m_material->getShader()->getProgramID(), "vTextureCoord");

		glEnableVertexAttribArray(vPosition);
		if(vTextureCoord != -1)
			glEnableVertexAttribArray(vTextureCoord);

		GLint uMvp           = glGetUniformLocation(m_material->getShader()->getProgramID(), "uMVP");

		glUniformMatrix4fv(uMvp, 1, false, glm::value_ptr(mvp));

		glVertexAttribPointer(vPosition, 3, GL_FLOAT, false, 3*sizeof(float), BUFFER_OFFSET(NULL));
		if(vTextureCoord != -1)
			glVertexAttribPointer(vTextureCoord, 2, GL_FLOAT, false, 2*sizeof(float), BUFFER_OFFSET(4 * 3 * sizeof(float) * strlen(m_text)));

		for(uint32_t i=0; i < strlen(m_text); i++)
			glDrawArrays(GL_TRIANGLE_STRIP, i*4, 4);
	}
	m_material->unbindTexture();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const Font* Text::getFont() const
{
	return m_font;
}

const char* Text::getText() const
{
	return m_text;
}

void Text::initVbos(float* letterCoords, float* textureCoords)
{
	deleteVbos();
	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		int size = 4 * sizeof(float) * strlen(m_text);
		//3 for letterCoord and 2 for textureCoord
		glBufferData(GL_ARRAY_BUFFER, 5*size, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 3*size, letterCoords);
		glBufferSubData(GL_ARRAY_BUFFER, 3*size, 2*size, textureCoords);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
