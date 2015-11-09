#ifndef FONT_INCLUDE
#define FONT_INCLUDE

#define CHAR_START         32
#define CHAR_END           127
#define CHAR_UNKNOWN       32
#define CHAR_CR            13
#define CHAR_NL            10
#define CHARACTERS_PER_ROW 16
#define GLM_FORCE_RADIANS

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <jni.h>
#include "Texture.h"
#include "Bitmap.h"
#include "Color.h"
#include "JniMadeOf.h"

/** \brief The edges (or the metrics) of the Font.*/
struct FontMetrics
{
	float ascent; /** The recommended distance above the baseline for singled spaced text. */
	float descent; /** The maximum distance below the baseline for the lowest glyph in the font at a given text size.*/
	float bottom; /** The recommended distance below the baseline for singled spaced text. */
	float leading; /** The recommended additional space to add between lines of text.*/
	float top; /** The maximum distance above the baseline for the tallest glyph in the font at a given text size.*/

	jobject fontMetrics;
};

/** \brief The font object generate by a font file. */
class Font : public JniMadeOf
{
	public:
		/** \brief Init the font generated before and store in the texture.
		 * \param texture Where the characters of the font is graphicly stored.
		 * \param charWidth Array of the width of each characters.
		 * \param charHeight Array of the height of each characters.
		 * \param posX Array of the x position of each characters.
		 * \param posY Array of the y position of each characters.
		 * \param maxHeight the maximum character height.
		 * \param maxWidth the maximum character width.
		 * \param padX the width space between each character's columns.
		 * \param padY the height space between each character's rows
		 * \param fontMetrics the font metrics of this font.*/
		Font(Texture* texture, int* charWidth, int* charHeight, int* posX, int* posY, int maxWidth, int maxHeight, int padX, int padY, FontMetrics& fontMetrics);

		/** \brief get the position in pixel of the character in directX norme. 
		 * Remember that the character position is given from its baseline, and not the top if it.
		 * \param character the character ascii
		 * \return the position of pixel of this character*/
		glm::vec2 getPosition(char character) const;

		/** \brief get the size in pixel of the character
		 * \param character the character ascii code
		 * \return the size of the character*/
		glm::vec2 getSize(char character) const;

		/** \brief get the rectangle of this character in directX norme.
		 * \param character the character ascii code
		 * \return the rect of this character*/
		FloatRect2 getCharRect(char character) const;

		/** \brief get the texture used for this font.
		 * \return the texture of the font, containing all the character used*/
		const Texture* getTexture() const;

		/** \brief get the height of one line of this font.
		 * \return the height of one line of this font.*/
		float getLineHeight() const;

		/** \brief get the font metrics of this font
		 * \return the font metrics.*/
		const FontMetrics& getFontMetrics() const;

		/** \brief create a font from assets. It need the java lib associated with this file
		 * \param path the file path on the assets directory
		 * \param padX the x space between each character
		 * \param padY the y space between each character
		 * \param size the character size on the texture */
		static Font* fontFromAssets(const std::string path, uint32_t padX=1, uint32_t padY=1, uint32_t size=36);
	private:
		std::vector<glm::vec2> m_charSize;
		std::vector<glm::vec2> m_charPos;
		glm::vec2              m_maxSize;
		glm::vec2              m_pad;

		Texture*              m_texture;
		FontMetrics           m_fontMetrics;
};

#endif
