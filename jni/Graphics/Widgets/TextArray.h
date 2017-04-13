#ifndef  TEXTARRAY_INC
#define  TEXTARRAY_INC

#include "Drawable.h"
#include "TextInterface.h"
#include "Text.h"

enum TextArrayCutting{BY_CHAR, BY_WORD};

class TextArray : public Text
{
	public:
		/** \brief The constructor to create TextArray
		 * \param parent the parent of the Widget
		 * \param mtl the material to draw the text
		 * \param font the font of the text
		 * \param text the text of the TextArray
		 * \param lineLength the length lines can't go over*/
		TextArray(Updatable* parent, Material* mtl, const Font* font, const std::string& text="", double lineLength=1.0, TextArrayCutting cutting=BY_CHAR);

		void setText(const char* text);
		void setLineLength(double lineLength);
		void setCutting(TextArrayCutting cutting);

		double getLineLength() const {return m_lineLength;}
		const char* getText() const {return m_textNotModified.c_str();}
		TextArrayCutting getCutting() const {return m_cutting;}
	private:
		double m_lineLength=1.0;
		std::string m_textNotModified;
		TextArrayCutting m_cutting=BY_CHAR;
};

#endif
