#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <limits>

#include "datatype.hpp"
#include "enviroment.hpp"
#include "error.hpp"


namespace Xigua
{
	namespace FunctionUtils
	{

		std::vector<DataType> parse_arguments(std::vector<DataType> arguments, int nonrepeating)
		{
			std::vector<DataType> return_list;
			for (int i(0); i < arguments.size(); i++) {
				if (i < nonrepeating) {
					return_list.push_back(arguments.at(i));
				} else {
					for (auto j : arguments.at(i).tuple())
						return_list.push_back(j);
				}
			}

			return return_list;
		}

		bool all_types_are(std::vector<DataType> arguments, DataTypes expected)
		{
			for (auto argument : arguments)
			{
				if (argument.type() != expected)
					return false;
			}
			return true;
		}

	}
}