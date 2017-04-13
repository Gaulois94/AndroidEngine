#ifndef  TEXTINTERFACE_INC
#define  TEXTINTERFACE_INC

#include<cstring>
#include "Font.h"

class TextInterface
{
	public:
		TextInterface(const Font* font, const char* text);

		~TextInterface();

		/** \brief set the font of the text
		 * \param font the new font. The user should store the font somewhere (for example on a ResourcesManager) */
		virtual void setFont(const Font* font);

		/** \brief set the text string.
		 * \param text the new string */
		virtual void setText(const char* text);

		/** \brief get the text font.
		 * \return the font associated with the text.*/
		const Font* getFont() const;

		/** \brief get the text string.
		 * \return the text string.*/
		virtual const char* getText() const; //Need to be virtual (the text shown is not the text entered)

		/** \brief add a character to the text.
		 * Following it's value, it can be rejected (like shift control), removing char (backspace, delete) or adding the char at the position
		 * \param c the character to add at the position pos
		 * \param pos the position where to add the character. -1 = at the end of the text*/
		void addChar(uint8_t c, int pos=-1);
	protected:
		const Font*  m_font;
		char*        m_text;

};

#endif
