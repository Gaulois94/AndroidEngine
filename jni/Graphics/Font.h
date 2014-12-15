#ifndef FONT_INCLUDE
#define FONT_INCLUDE

#define CHAR_START         32
#define CHAR_END           127
#define CHAR_UNKNOWN       32
#define CHAR_CR            13
#define CHAR_NL            10
#define CHARACTERS_PER_ROW 16

class Font
{
	public:
		Font();
	private:
		std::vector<int> m_charWidth;
		std::vector<int> m_charHeight;
		std::vector<int> m_charPosX;
		std::vector<int> m_charPosY;

		int m_maxWidth;
		int m_maxHeight;
		int m_padX;
		int m_padY;
};

#endif
