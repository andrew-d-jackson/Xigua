#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <limits>

#include "datatype.hpp"
#include "enviroment.hpp"
#include "error.hpp"


namespace xig
{
	namespace FunctionUtils
	{

		std::vector<data> parse_arguments(std::vector<data> arguments, unsigned int nonrepeating)
		{
			std::vector<data> return_list;
			for (unsigned int i(0); i < arguments.size(); i++) {
				if (i < nonrepeating) {
					return_list.push_back(arguments.at(i));
				} else {
					for (auto j : arguments.at(i).tuple())
						return_list.push_back(j);
				}
			}

			return return_list;
		}

		bool all_types_are(std::vector<data> arguments, data_type expected)
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