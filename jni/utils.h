#ifndef DEF_UTILS_INCLUDE
#define DEF_UTILS_INCLUDE

#include <vector>
#include <string>
#include <sstream>

/* brief split the string by a char delimiter
 * \param buffer the string whose will be split
 * \param delim the char delimiter 
 * \return the array of results*/
std::vector<std::string> split(const std::string& buffer, char delim);

#endif
