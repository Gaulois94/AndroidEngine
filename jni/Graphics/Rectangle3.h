#ifndef DEF_RECTANGLE3_INCLUDE
#define DEF_RECTANGLE3_INCLUDE

template<typename T>
class Rectangle3<T>
{
	public:
		Rectangle3<T>(T a, T b, T c, T w, T h, T d)
		{
			x      = a;
			y      = b;
			z      = c;
			width  = w;
			height = h;
			depth  = d;
		}

		T x;
		T y;
		T z;
		T width;
		T height;
		T depth;
};

template<typename T>
bool operator==(const Rectangle3<T> &a, const Rectangle3<T> &b)
{
	return(a.x == b.x && a.y == b.y && a.z == b.z && a.width == b.width && a.height == b.height && a.depth == b.depth);
}

template<typename T>
bool operator!=(const Rectangle3<T> &a, const Rectangle3<T> &b)
{
	return(!(a==b));
}

template<typename T>
Rectangle3<T> operator+(const Rectangle3<T> &a, const Rectangle3<T> &b)
{
	return Rectangle3<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.width + b.width, a.height + b.height, a.depth + b.depth);
}

template<typename T>
Rectangle3<T> operator-(const Rectangle3<T> &a, const Rectangle3<T> &b)
{
	return Rectangle3<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.width - b.width, a.height - b.height, a.depth - b.depth);
}

typedef Rectangle3<float> FloatRect3;
typedef Rectangle3<int>   IntRect3;

#endif
