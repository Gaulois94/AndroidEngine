#ifndef RECT_INCLUDE
#define RECT_INCLUDE

template<typename T>
class Rectangle2
{
	public:
		Rectangle2(T a=0.0f, T b=0.0f, T w=0.0f, T h=0.0f)
		{
			x = a;
			y = b;
			width = w;
			height = h;
		}

		Rectangle2(const Rectangle2<T>& r)
		{
			x = r.x;
			y = r.y;
			width = r.width;
			height = r.height;
		}

		Rectangle2<T>& operator=(const Rectangle2<T>& r)
		{
			if(this != &r)
			{
				x = r.x;
				y = r.y;
				width = r.width;
				height = r.height;
			}

			return *this;
		}

		T x;
		T y;
		T width;
		T height;
};

template<typename T>
bool operator==(const Rectangle2<T> &a, const Rectangle2<T> &b)
{
	return(a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height);
}

template<typename T>
bool operator!=(const Rectangle2<T> &a, const Rectangle2<T> &b)
{
	return(!(a==b));
}

template<typename T>
Rectangle2<T> operator+(const Rectangle2<T> &a, const Rectangle2<T> &b)
{
	return Rectangle2<T>(a.x + b.x, a.y + b.y, a.width + b.width, a.height + b.height);
}

template<typename T>
Rectangle2<T> operator-(const Rectangle2<T> &a, const Rectangle2<T> &b)
{
	return Rectangle2<T>(a.x - b.x, a.y - b.y, a.width - b.width, a.height - b.height);
}

typedef Rectangle2<float> FloatRect2;
typedef Rectangle2<int>   IntRect2;

#endif
