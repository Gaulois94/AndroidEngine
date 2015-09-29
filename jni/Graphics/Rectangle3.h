#ifndef DEF_RECTANGLE3_INCLUDE
#define DEF_RECTANGLE3_INCLUDE

/** \brief the 3D rectangle operations.*/
template<typename T>
class Rectangle3<T>
{
	public:
		/** \brief Init the 3D rectangle coordinates.
		 * \param a the x coordinate
		 * \param b the y coordinate
		 * \param c the z coordinate
		 * \param w the width
		 * \param h the height
		 * \param d the depth*/
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

typedef Rectangle3<float> FloatRect3;
typedef Rectangle3<int>   IntRect3;

#endif
