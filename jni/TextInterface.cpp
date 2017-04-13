#include "TextInterface.h"

TextInterface::TextInterface(const Font* font, const char* text) : m_font(NULL), m_text(NULL)
{
	setFont(font);
	setText(text);
}

TextInterface::~TextInterface()
{
	if(m_text)
		free(m_text);
}

void TextInterface::setFont(const Font* font)
{
	m_font = font;
}

void TextInterface::setText(const char* text)
{
	if(text != m_text)
	{
		if(m_text != NULL)
			free(m_text);

		//We copy the new text and store it
		m_text = (char*) malloc((strlen(text)+1)*sizeof(char));
		strcpy(m_text, text);
		m_text[strlen(text)] = '\0';
	}
}

const Font* TextInterface::getFont() const
{
	return m_font;
}

const char* TextInterface::getText() const
{
	return m_text;
}

void TextInterface::addChar(uint8_t c, int pos)
{
	if(pos == -1)
		pos = strlen(m_text);

	char* text = (char*)malloc((strlen(m_text)+2)*sizeof(char));
	strcpy(text, m_text);

	if(c=='\b')
	{
		for(int i=pos-1; i < strlen(text); i++)
			text[i] = text[i+1];
	}

	//DEL command
	else if(c==0x7f)
	{
		for(int i=pos; i < strlen(text); i++)
			text[i] = text[i+1];
	}

	else if(c >= ' ' && c <= '~')
	{
		for(int i=strlen(text)+1; i > pos; i--)
			text[i] = text[i-1];
		text[pos] = c;
	}

	else
	{
		free(text);
		return;
	}

	setText(text);
	free(text);
}
