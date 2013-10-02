#pragma once

#include <vector>
#include <string>
#include <functional>
#include <limits>
#include <algorithm>

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

			DataType unique(std::vector<DataType> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				if (inputs.at(0).type() != DataTypes::Tuple)
					throw Xigua::Error(Xigua::ErrorTypes::INVALID_ARGS, "Not A Tuple", function_call_list);

				auto initial_tuple = inputs.at(0).tuple();
				std::sort(initial_tuple.begin(), initial_tuple.end());
				auto unique_iterator = std::unique(initial_tuple.begin(), initial_tuple.end());
				std::vector<DataType> return_value(initial_tuple.begin(), unique_iterator);

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

			DataType range(std::vector<DataType> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				if (!FunctionUtils::all_types_are(inputs, DataTypes::Number))
					throw Xigua::Error(Xigua::ErrorTypes::INVALID_ARGS, "Not A Number", function_call_list);

				long double start = inputs.at(0).number();
				long double end = inputs.at(1).number();
				long double step = inputs.at(2).number();

				if (start > end && step >= 0)
					throw Xigua::Error(Xigua::ErrorTypes::INVALID_ARGS, "Range Invalid", function_call_list);
				else if (start < end && step <= 0)
					throw Xigua::Error(Xigua::ErrorTypes::INVALID_ARGS, "Range Invalid", function_call_list);
				else if (step == 0 || start == end)
					throw Xigua::Error(Xigua::ErrorTypes::INVALID_ARGS, "Range Invalid", function_call_list);


				std::vector<DataType> return_value;

				if (start > end) {
					while (start > end) {
						return_value.push_back(DataType(DataTypes::Number, start));
						start += step;
					}
				} else if (start < end) {
					while (start < end) {
						return_value.push_back(DataType(DataTypes::Number, start));
						start += step;
					}
				}

				return DataType(DataTypes::Tuple, return_value);
			}


		}
	}
}