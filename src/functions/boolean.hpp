#pragma once

#include <vector>
#include <string>
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
		namespace Boolean
		{

			DataType boolean_not(std::vector<DataType> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				if (inputs.at(0).type() != DataTypes::Bool)
					throw Xigua::Error(Xigua::ErrorTypes::INVALID_ARGS, "Not A Boolean", function_call_list);

				return DataType(DataTypes::Bool, !(inputs.at(0).boolean()));
			}

		}
	}
}