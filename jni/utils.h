#ifndef DEF_UTILS_INCLUDE
#define DEF_UTILS_INCLUDE

#include <vector>
#include <string>
#include <sstream>
#include "Rectangle2.h"
#include "Rectangle3.h"
#include "JniMadeOf.h"
#include <sstream>
#include <algorithm>

/* brief split the string by a char delimiter
 * \param buffer the string whose will be split
 * \param delim the char delimiter 
 * \return the array of results*/
std::vector<std::string> split(const std::string& buffer, char delim);

/** \brief Get the rectangle intersection between 2 Rectangle2
 * \param r1 the first rectangle
 * \param r2 the second rectangle
 * \return the intersection between those rectangles*/
template <typename T>
Rectangle2<T> getRectIntersect(const Rectangle2<T>& r1, const Rectangle2<T>& r2)
{
	float xMin, xMax, yMin, yMax;
	xMin = fmax(r1.x, r2.x);
	xMax = fmin(r1.x + r1.width, r2.x + r2.width);
	yMin = fmax(r1.y, r2.y);
	yMax = fmin(r1.y + r1.height, r2.y + r2.height);

	return Rectangle2<T>(xMin, yMin, fmax(xMax-xMin, T(0.0)), fmax(yMax-yMin, T(0.0)));
}

/** \brief Get the rectangle intersection between 2 Rectangle3
 * \param r1 the first rectangle
 * \param r2 the second rectangle
 * \return the intersection between those rectangles*/
template <typename T>
Rectangle3<T> getRectIntersect(const Rectangle3<T>& r1, const Rectangle3<T>& r2)
{
	float xMin, xMax, yMin, yMax, zMin, zMax;
	xMin = fmax(r1.x, r2.x);
	xMax = fmin(r1.x + r1.width, r2.x + r2.width);
	yMin = fmax(r1.y, r2.y);
	yMax = fmin(r1.y + r1.height, r2.y + r2.height);

	zMin = fmax(r1.z, r2.z);
	zMax = fmin(r1.z + r1.depth, r2.z + r2.depth);

	return Rectangle3<T>(xMin, yMin, zMin, fmax(xMax - xMin, (T)(0.0)), fmax(yMax - yMin, (T)(0.0)), fmax(zMax - zMin, (T)(0.0)));
}

/** \brief Get the minimal rectangle which contains 2 Rectangle3
 * \param r1 the first rectangle
 * \param r2 the second rectangle
 * \return the global Rectangle3 between those rectangles*/
template <typename T>
Rectangle3<T> getRectAddiction(const Rectangle3<T>& r1, const Rectangle3<T>& r2)
{
	Rectangle3<T> r = Rectangle3<T>(fmin(r1.x, r2.x), fmin(r1.y, r2.y), fmin(r1.z, r2.z),
									fmax(r1.x + r1.width, r2.x + r2.width), 
									fmax(r1.y + r1.height, r2.y + r2.height), 
									fmax(r1.z + r1.depth, r2.z + r2.depth));
	r.width = r.width - r.x;	
	r.height = r.height - r.y;	
	r.depth = r.depth - r.z;	

	return r;
}

/** \brief get a text from resources files
 * \param id the ID of the resource without the R (string.app_name for example)
 * \return the text of the resource*/
std::string getTextFromRes(const std::string& id);

#endif
