#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <limits>

#include "../datatype.hpp"
#include "../enviroment.hpp"
#include "../functionutils.hpp"
#include "../error.hpp"


namespace Xigua
{
	namespace Functions
	{
		namespace String
		{

			DataType concatinate(std::vector<DataType> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 1);

				std::string return_string = "";
				for (auto argument : arguments) {
					return_string += argument.as_string();
				}

				return DataType(DataTypes::String, return_string);
			}

		}
	}
}