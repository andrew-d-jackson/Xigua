#include <string>
#include <sstream>
#include <fstream>

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

std::string read_file(std::string filename)
{
	std::ifstream t(filename.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();	
}
