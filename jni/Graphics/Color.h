#ifndef DEF_COLOR_INCLUDE
#define DEF_COLOR_INCLUDE

class Color
{
	public:
		//red, green, blue and alpha must to be between 0.0f and 1.0f
		Color(float red=0.0f, float green=0.0f, float blue=0.0f, float alpha=1.0f);
		Color(const Color& c);
		Color operator=(const Color& c);
		float r;
		float g;
		float b;
		float a;
};

#endif
