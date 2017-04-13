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
		switch(m_cutting)
		{
			case BY_CHAR:
				//we start at the start of the line (of course)
				double posX       = 0.0f;
				bool hasStartLine = false;

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
					LOG_ERROR("POS X %f %s", (float)posX, newText.c_str());

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

			case BY_WORD:
				//TODO
				break;
		}

		Text::setText(newText.c_str());
	}

	else
		Text::setText(text);
}
