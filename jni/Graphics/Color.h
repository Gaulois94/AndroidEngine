#ifndef DEF_COLOR_INCLUDE
#define DEF_COLOR_INCLUDE

class Color
{
	public:
		//red, green, blue and alpha must to be between 0.0f and 1.0f
		Color(float red=0.0f, float green=0.0f, float blue=0.0f, float alpha=1.0f);
		Color(const Color& c);
		Color(float* color);
		Color operator=(const Color& c);
		void getFloatArray(float* array) const;
		float r;
		float g;
		float b;
		float a;

		static const Color WHITE;
		static const Color BLACK;
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		static const Color MAGENTA;
		static const Color YELLOW;
		static const Color CYAN;

		static const Color TRANSPARENT;
};

#endif
