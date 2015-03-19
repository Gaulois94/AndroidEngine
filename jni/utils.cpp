#include "utils.h"

std::vector<std::string> split(const std::string& buffer, char delim)
{
	std::vector<std::string> r;
	std::istringstream iss(buffer);
	std::string s;
	while(getline(iss, s, delim))
		r.push_back(s);
	return r;
}
