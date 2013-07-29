#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <limits>

#include "datatype.hpp"
#include "enviroment.hpp"


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

		void wrong_type_error(std::string function_name)
		{
			std::cout << "----------------------" << std::endl;
			std::cout << "Error:" << std::endl;
			std::cout << "Wrong Type In Function " << function_name << std::endl;
			exit(1);
		}

		void assert_all_types_are(std::string function_name, std::vector<DataType> arguments, DataTypes expected)
		{
			for (auto argument : arguments)
			{
				if (argument.type() != expected)
					wrong_type_error(function_name);
			}
		}

	}
}