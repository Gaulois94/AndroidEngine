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

struct FontMetrics
{
	float ascent;
	float descent;
	float bottom;
	float leading;
	float top;

	jobject fontMetrics;
};

class Font
{
	public:
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
