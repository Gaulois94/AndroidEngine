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
#include "Texture.h"
#include "Bitmap.h"
#include "Color.h"

/** \brief The edges (or the metrics) of the Font */
struct FontMetrics
{
	float ascent;
	float descent;
	float bottom;
	float leading;
	float top;

	jobject fontMetrics;
};

/** \brief The font object generate by a font file. */
class Font
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

		glm::vec2 getPosition(char character) const;
		glm::vec2 getSize(char character) const;
		const Texture* getTexture() const;
		float getLineHeight() const;
		const FontMetrics& getFontMetrics() const;
	private:
		std::vector<glm::vec2> m_charSize;
		std::vector<glm::vec2> m_charPos;
		glm::vec2              m_maxSize;
		glm::vec2              m_pad;

		Texture*              m_texture;
		FontMetrics           m_fontMetrics;
};

#endif
