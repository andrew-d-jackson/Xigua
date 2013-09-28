#include "helpers.hpp"


bool is_number(std::string string)
{
	if (string.size() < 1)
		return false;
		
	for (char c : string)
	{
		if (!isdigit(c) && c != '.')
			return false;
	}

	return true;
}