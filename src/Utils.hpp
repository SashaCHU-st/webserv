#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

class Utils {
	public:
		static std::vector<std::string> splitStr (const std::string& str, std::string delim);
};

#endif