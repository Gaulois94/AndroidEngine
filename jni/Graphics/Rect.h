#ifndef RECT_INCLUDE
#define RECT_INCLUDE

template<typename T>
class Rect<T>
{
	public:
		Rect(T a, T b, T w, T h)
		{
			x = a;
			y = b;
			width = w;
			height = h;
		}

		T x;
		T y;
		T width;
		T height;
};

template<typename T>
bool operator==(const Rect<T> &a, const Rect<T> &b)
{
	return(a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height);
}

template<typename T>
Rect<T> operator+(const Rect<T> &a, const Rect<T> &b)
{
	return Rect<T>(a.x + b.x, a.y + b.y, a.width + b.width, a.height + b.height);
}

template<typename T>
Rect<T> operator-(const Rect<T> &a, const Rect<T> &b)
{
	return Rect<T>(a.x - b.x, a.y - b.y, a.width - b.width, a.height - b.height);
}

template<typename T>
Rect<T> operator*(const Rect<T> &a, float x)
{
	return Rect<T>(a.x * x, a.y * x, a.width * x, a.height * x);
}

template<typename T>
Rect<T> operator*(float x, const Rect<T> &a)
{
	return a*x;
}

template<typename T>
Rect<T> operator/(const Rect<T> &a, float x)
{
	return a * (1/x);
}

typedef Rect<float> FloatRect;

#endif
