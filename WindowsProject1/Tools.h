#pragma once
#include <sstream>
#include <algorithm>

const char* ConvertIntToConstChar(int i) {
	
	std::ostringstream oss;
	oss << i;
	std::string result = oss.str();

	char* cstr = new char[result.length() + 1];
	size_t oue = result.length() + 1;
	std::copy(result.c_str(), result.c_str() + result.length() + 1, cstr);

	return cstr;
}