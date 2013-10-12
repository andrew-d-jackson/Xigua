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


namespace xig
{
	namespace Functions
	{
		namespace String
		{

			data concatinate(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
			{
				auto arguments = xig::FunctionUtils::parse_arguments(inputs, 1);

				std::string return_string = "";
				for (auto argument : arguments) {
					return_string += argument.as_string();
				}

				return data(data_type::String, return_string);
			}

		}
	}
}