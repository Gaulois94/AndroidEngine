#ifndef  TEXTENTRY_INC
#define  TEXTENTRY_INC

#include "Shape/Rectangle.h"
#include "Drawable.h"
#include "Text.h"
#include "TextInterface.h"
#include "Keyboard.h"

#define CURSOR_SCALE 30.0f
#define CURSOR_ANIM  25

/** \class TextEntry
 * \brief The TextEntry Widget. Use for entering and getting text.*/
class TextEntry : public Drawable, public TextInterface
{
	public:
		/** \brief The constructor. The Widget is composed of a Rectangle and a Text Drawable object.
		 * \param parent the parent of the Widget
		 * \param textMaterial the material applied to the Text
		 * \param font the Font applied to the Text
		 * \param defaultText the descriptif text of the Widget. Is removed on the first focus.
		 * \param backgroundMaterial the Material of the Background object
		 * \param firstTextMaterial the Material applied to the Text on its descriptif form. If NULL, the material is the same as the textMaterial.*/
		TextEntry(Updatable* parent, Material* textMaterial, const Font* font, const std::string& defaultText, Material* backgroundMaterial, Material* cursorMaterial=NULL, Material* firstTextMaterial=NULL);

		void onUpdate(Render& render);
		void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void onFocus(const TouchEvent& te, Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		bool onKeyDown(int32_t key);
		void updateTextPosition();

		void setFont(const Font* font);
		void setText(const char* text);

		void setBackgroundScale(const glm::vec3& scale);
		void setTextScale(const glm::vec3& scale);

		/** \brief get the maximum number of character the TextEntry can have
		 * \return the maximum number of character. Negative numbers = no limits*/
		int32_t getMaxChar() const{return m_maxChar;}

		/** \brief tell if the characters are hidden on the screen
		 * \return the hidden caracteristics of the characters*/
		bool isCharHidden() const{return m_hideChar;}

		/** \brief set the hidden caracteristics of the characters shown on the screen
		 * \param h shall the characters be hidden or not.*/
		void setHiddenChar(bool h);

		/** \brief set the maximum number of character the TextEntry can have. Over limit characters will be deleted 
		 * \param limit the new maximum number of character. Negative numbers = no limits*/
		void setMaxChar(int32_t limit);

		const Rectangle& getBackground() const;
		const Text& getTextDrawable() const;
		void setRequestSize(const glm::vec3& scale, bool keepPos=true);
	private:
		bool m_firstFocus=false;
		Material* m_textMaterial;
		Rectangle m_rectangle;
		Text m_textDrawable;
		uint32_t m_cursorPosition=0;
		Material* m_cursorMaterial;
		Rectangle m_cursor;
		uint32_t m_cursorAnim = 0;
		bool     m_showCursor = true;
		bool     m_isWriting  = false;
		bool     m_hideChar   = false;
		int32_t  m_maxChar    = -1;
};

#endif
