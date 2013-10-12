#pragma once

#include <vector>
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
		namespace Math
		{

			data less_than(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				auto arguments = xig::FunctionUtils::parse_arguments(inputs, 2);
				if (!xig::FunctionUtils::all_types_are(arguments, data_type::Number))
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Number", function_call_list);


				long double previous_number = arguments.at(0).number();
				for (unsigned int i(1); i < arguments.size(); i++)
				{
					if (previous_number < arguments.at(i).number()){
						previous_number = arguments.at(i).number();
					} else {
						return data(data_type::Bool, false); 
					}
				}

				return data(data_type::Bool, true);
			}

			data greater_than(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				auto arguments = xig::FunctionUtils::parse_arguments(inputs, 2);
				if (!xig::FunctionUtils::all_types_are(arguments, data_type::Number))
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Number", function_call_list);

				long double previous_number = arguments.at(0).number();
				for (unsigned int i(1); i < arguments.size(); i++)
				{
					if (previous_number > arguments.at(i).number()){
						previous_number = arguments.at(i).number();
					} else {
						return data(data_type::Bool, false); 
					}
				}

				return data(data_type::Bool, true);
			}

			data equal_to(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				auto arguments = xig::FunctionUtils::parse_arguments(inputs, 2);

				for (unsigned int i(1); i < arguments.size(); i++)
				{
					if (arguments.at(0) != arguments.at(i)){
						return data(data_type::Bool, false); 
					}
				}

				return data(data_type::Bool, true);
			}

			data add(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				auto arguments = xig::FunctionUtils::parse_arguments(inputs, 2);
				if (!xig::FunctionUtils::all_types_are(arguments, data_type::Number))
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Number", function_call_list);

				long double return_value = arguments.at(0).number();
				for (unsigned int i(1); i < arguments.size(); i++)
				{
					return_value += arguments.at(i).number();
				}

				return data(data_type::Number, return_value);
			}

			data minus(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				auto arguments = xig::FunctionUtils::parse_arguments(inputs, 2);
				if (!xig::FunctionUtils::all_types_are(arguments, data_type::Number))
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Number", function_call_list);

				long double return_value = arguments.at(0).number();
				for (unsigned int i(1); i < arguments.size(); i++)
				{
					return_value -= arguments.at(i).number();
				}

				return data(data_type::Number, return_value);
			}

			data multiply(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				auto arguments = xig::FunctionUtils::parse_arguments(inputs, 2);
				if (!xig::FunctionUtils::all_types_are(arguments, data_type::Number))
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Number", function_call_list);

				long double return_value = arguments.at(0).number();
				for (unsigned int i(1); i < arguments.size(); i++)
				{
					return_value *= arguments.at(i).number();
				}

				return data(data_type::Number, return_value);
			}

			data divide(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				auto arguments = xig::FunctionUtils::parse_arguments(inputs, 2);
				if (!xig::FunctionUtils::all_types_are(arguments, data_type::Number))
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Number", function_call_list);

				long double return_value = arguments.at(0).number();
				for (unsigned int i(1); i < arguments.size(); i++)
				{
					return_value /= arguments.at(i).number();
				}

				return data(data_type::Number, return_value);
			}

		}
	}
}