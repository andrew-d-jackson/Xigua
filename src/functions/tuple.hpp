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
		namespace Tuple
		{

			DataType join(std::vector<DataType> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 2);

				std::vector<DataType> return_value;
				for (auto argument : arguments)
				{
					if (argument.type() == DataTypes::Tuple) {
						for (auto element : argument.tuple())
							return_value.push_back(element);
					} else {
						return_value.push_back(argument);
					}
				}

				return DataType(DataTypes::Tuple, return_value);
			}

			DataType first(std::vector<DataType> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				if (inputs.at(0).type() != DataTypes::Tuple)
					throw Xigua::Error(Xigua::ErrorTypes::INVALID_ARGS, "Not A Tuple", function_call_list);

				if (inputs.at(0).tuple().size() < 1)
					throw Xigua::Error(Xigua::ErrorTypes::INVALID_ARGS, "Not In Range", function_call_list);

				return inputs.at(0).tuple().at(0);
			}

			DataType last(std::vector<DataType> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				if (inputs.at(0).type() != DataTypes::Tuple)
					throw Xigua::Error(Xigua::ErrorTypes::INVALID_ARGS, "Not A Tuple", function_call_list);

				if (inputs.at(0).tuple().size() < 1)
					throw Xigua::Error(Xigua::ErrorTypes::INVALID_ARGS, "Not In Range", function_call_list);

				return inputs.at(0).tuple().at(inputs.at(0).tuple().size()-1);
			}


		}
	}
}