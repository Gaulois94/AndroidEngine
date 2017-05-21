#include "Widgets/TextArray.h"

TextArray::TextArray(Updatable* parent, Material* mtl, const Font* font, const std::string& text, double lineLength, TextArrayCutting cutting) : Text(parent, mtl, font, text.c_str()), m_lineLength(lineLength), m_cutting(cutting)
{
	setText(text.c_str());
}

void TextArray::setLineLength(double lineLength)
{
	m_lineLength = lineLength;
	setText(m_textNotModified.c_str());
}

void TextArray::setText(const char* text)
{
	m_textNotModified   = text;
	std::string newText;

	if(m_font && text)
	{
		//we start at the start of the line (of course)
		double posX       = 0.0f;
		bool hasStartLine = false;

		switch(m_cutting)
		{
			case BY_CHAR:
			{
				for(unsigned int i=0; m_text[i] != '\0'; i++)
				{
					//If the character is \n, we jump to the next line
					if(text[i] == CHAR_NL)
					{
						newText += text[i];
						posX = 0;
						hasStartLine = false;
						continue;
					}

					glm::vec2 size = m_font->getSize(m_text[i])/m_font->getLineHeight();
					posX += size.x;

					if(posX >= m_lineLength && hasStartLine)
					{
						i--;
						posX = 0;
						hasStartLine = false;
						newText += CHAR_NL;
						continue;
					}
					newText += text[i];
					hasStartLine = true;
				}
				break;
			}

			case BY_WORD:
			{
				//we start at the start of the line (of course)
				bool firstWord    = true;

				for(unsigned int i=0; m_text[i] != '\0'; i++)
				{
					//If the character is \n, we jump to the next line
					if(text[i] == CHAR_NL)
					{
						newText += text[i];
						posX = 0;
						hasStartLine = false;
						continue;
					}

					else if(text[i] == ' ')
					{
						//If it is the first space of a new line, discard it
						if(i > 0 && m_text[i-1] != ' ' && m_text[i-1] != CHAR_NL && posX == 0)
							continue;

						if(i > 0 && text[i-1] != ' ' && text[i-1] != CHAR_NL)
							firstWord = false;

						glm::vec2 size = m_font->getSize(m_text[i])/m_font->getLineHeight();
						posX += size.x;

						//Too much space, we break the line
						if(posX >= m_lineLength && hasStartLine)
						{
							i--;
							posX = 0;
							hasStartLine = false;
							newText += CHAR_NL;
							continue;
						}
						hasStartLine;
						newText += text[i];
					}

					else
					{
						glm::vec2 size = m_font->getSize(m_text[i])/m_font->getLineHeight();
						posX += size.x;

						//First word of the line, need to be broken
						if(firstWord && hasStartLine && posX >= m_lineLength)
						{
							i--;
							posX = 0;
							hasStartLine = false;
							newText += CHAR_NL;
							continue;
						}

						//The next word is too long
						else if(i > 0 && text[i-1] == ' ' && posX >= m_lineLength && hasStartLine)
						{
							i--;
							posX = 0;
							hasStartLine = false;
							newText += CHAR_NL;
							continue;
						}

						newText += text[i];
						hasStartLine = true;
					}

				}
				break;
			}
		}

		Text::setText(newText.c_str());
	}

	else
		Text::setText(text);
}
