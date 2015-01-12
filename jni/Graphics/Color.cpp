#include "Color.h"

Color::Color(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha)
{}

Color::Color(const Color& color) : r(color.r), g(color.g), b(color.b), a(color.a)
{
}

Color Color::operator=(const Color& color)
{
	if(this != &color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}
	return *this;
}
