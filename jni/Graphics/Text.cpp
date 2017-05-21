#include "Text.h"

Text::Text(Updatable* parent, Material* material, const Font* font, const std::string& text) : Drawable(parent, material), TextInterface(font, text.c_str())
{
	setText(text.c_str());
}

Text::Text() : Drawable(NULL, NULL), TextInterface(NULL, NULL)
{
}

void Text::setFont(const Font* font)
{
	TextInterface::setFont(font);
	setText(m_text);
}

void Text::setText(const char* text)
{
	TextInterface::setText(text);

	if(!m_font || !text)
	{
		setDefaultSize(glm::vec3(0.0f, 0.0f, 0.0f));//No text, no size
		return;
	}

	//A text is just a number of letter drawn one by one
	float *textureCoords = (float*) malloc(strlen(m_text) * 4 * 2 * sizeof(float));
	float *letterCoords = (float*) malloc(strlen(m_text) * 4 * 3 * sizeof(float));

	//We start at the position (0.0, 0.0)
	float maxPosX = 0.0f;
	float posX = 0.0f;
	float posY = 0.0f;

	for(unsigned int i=0; m_text[i] != '\0'; i++)
	{
		//If the character is \n, we jump to the next line (posY -= m_font->getLineHeight())
		if(text[i] == CHAR_NL)
		{
			maxPosX = fmax(maxPosX, posX);
			posX = 0;
			posY -= (float) m_font->getFontMetrics().leading + 1.0;

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

		glm::vec2 size = m_font->getSize(m_text[i])/(float)m_font->getLineHeight();

		float rectTextureCoord[] = {rectTexture.x, rectTexture.y,
									rectTexture.x + rectTexture.width, rectTexture.y,
									rectTexture.x, rectTexture.y + rectTexture.height,
									rectTexture.x + rectTexture.width, rectTexture.y + rectTexture.height};

		float rectLetterCoord[]  = {posX, posY, 0.0,
									posX + size.x, posY, 0.0,
									posX, posY + size.y, 0.0,
									posX + size.x, posY + size.y, 0.0};

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

	//Read just the default configuration of the Text object
	maxPosX = fmax(maxPosX, posX);
	setDefaultPos(glm::vec3(0.0f, posY, 0.0f));
	setDefaultSize(glm::vec3(maxPosX, -posY + 1, 0.0f));
	free(letterCoords);
	free(textureCoords);
}

void Text::onDraw(Render& render, const glm::mat4& mvp)
{
	if(m_font == NULL || m_text == NULL || m_material == NULL || !glIsBuffer(m_vboID))
		return;

	m_material->bindTexture(m_font->getTexture());
	m_material->init(render, mvp, getMatrix());
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	{
		GLint vPosition      = glGetAttribLocation(m_material->getShader()->getProgramID(), "vPosition");
		GLint vNormal        = glGetAttribLocation(m_material->getShader()->getProgramID(), "vNormal");
		GLint vTextureCoord  = glGetAttribLocation(m_material->getShader()->getProgramID(), "vTextureCoord");

		if(vNormal != -1)
			glVertexAttrib3f(vNormal, 0.0, 0.0, 1.0);

		glEnableVertexAttribArray(vPosition);

		GLint uMvp           = glGetUniformLocation(m_material->getShader()->getProgramID(), "uMVP");

		glUniformMatrix4fv(uMvp, 1, false, glm::value_ptr(mvp));

		glVertexAttribPointer(vPosition, 3, GL_FLOAT, false, 3*sizeof(float), BUFFER_OFFSET(0));
		if(vTextureCoord != -1)
		{
			glEnableVertexAttribArray(vTextureCoord);
			glVertexAttribPointer(vTextureCoord, 2, GL_FLOAT, false, 2*sizeof(float), BUFFER_OFFSET(4 * 3 * sizeof(float) * strlen(m_text)));
		}

		for(uint32_t i=0; m_text[i] != '\0'; i++)
			glDrawArrays(GL_TRIANGLE_STRIP, i*4, 4);

		glDisableVertexAttribArray(vPosition);
		if(vNormal != -1)
			glDisableVertexAttribArray(vNormal);
		if(vTextureCoord != -1)
			glDisableVertexAttribArray(vTextureCoord);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_material->unbindTexture();
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

glm::vec2 Text::getCharPosition(uint32_t index, bool useScale) const
{
	if(index > strlen(m_text))
		return glm::vec2(-1, -1);

	double posX=0, posY=0;

	for(unsigned int i=0; i < index; i++)
	{
		//If the character is \n, we jump to the next line (posY -= m_font->getLineHeight())
		if(m_text[i] == CHAR_NL)
		{
			posX = 0;
			posY -= 1.0;
		}

		glm::vec2 size = m_font->getSize(m_text[i])/m_font->getLineHeight();
		posX += size.x;
	}

	return (useScale) ? glm::vec2(posX, posY) * glm::vec2(getScale()) : glm::vec2(posX, posY);
}

int Text::getCharAt(float x, float y)
{
	double posX=0, posY=0;

	for(unsigned int i=0; m_text[i] != '\0'; i++)
	{
		glm::vec3 pos = glm::vec3(posX, posY, 0.0);
		glm::vec2 charSize = getCharSize(i);

		if(pos.x <= x && pos.x+charSize.x >= x &&
		   pos.y <= y && pos.y+charSize.y >= y)
			return i;

		//If the character is \n, we jump to the next line (posY -= m_font->getLineHeight())
		if(m_text[i] == CHAR_NL)
		{
			posX = 0;
			posY -= 1;
		}

		else
		{
			glm::vec2 size = m_font->getSize(m_text[i])/m_font->getLineHeight();
			posX += size.x;
		}

	}

	return -1;

}

glm::vec2 Text::getCharSize(uint32_t index) const
{
	return m_font->getSize(m_text[index])/m_font->getLineHeight();
}
