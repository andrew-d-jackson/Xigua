#include "math.hpp"

namespace xig {
namespace stdlib {

	data less_than(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		auto arguments = utils::parse_arguments(inputs, 2);
		if (!utils::all_types_are(arguments, data_type::Number))
			throw xig::error(xig::error_types::invalid_arguments, "Not A Number", function_call_list);


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

	data greater_than(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		auto arguments = utils::parse_arguments(inputs, 2);
		if (!utils::all_types_are(arguments, data_type::Number))
			throw error(error_types::invalid_arguments, "Not A Number", function_call_list);

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

	data equal_to(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		auto arguments = utils::parse_arguments(inputs, 2);

		for (unsigned int i(1); i < arguments.size(); i++)
		{
			if (arguments.at(0) != arguments.at(i)){
				return data(data_type::Bool, false); 
			}
		}

		return data(data_type::Bool, true);
	}

	data add(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		auto arguments = utils::parse_arguments(inputs, 2);
		if (!utils::all_types_are(arguments, data_type::Number))
			throw xig::error(xig::error_types::invalid_arguments, "Not A Number", function_call_list);

		long double return_value = arguments.at(0).number();
		for (unsigned int i(1); i < arguments.size(); i++)
		{
			return_value += arguments.at(i).number();
		}

		return data(data_type::Number, return_value);
	}

	data minus(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		auto arguments = utils::parse_arguments(inputs, 2);
		if (!utils::all_types_are(arguments, data_type::Number))
			throw xig::error(xig::error_types::invalid_arguments, "Not A Number", function_call_list);

		long double return_value = arguments.at(0).number();
		for (unsigned int i(1); i < arguments.size(); i++)
		{
			return_value -= arguments.at(i).number();
		}

		return data(data_type::Number, return_value);
	}

	data multiply(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		auto arguments = utils::parse_arguments(inputs, 2);
		if (!utils::all_types_are(arguments, data_type::Number))
			throw xig::error(xig::error_types::invalid_arguments, "Not A Number", function_call_list);

		long double return_value = arguments.at(0).number();
		for (unsigned int i(1); i < arguments.size(); i++)
		{
			return_value *= arguments.at(i).number();
		}

		return data(data_type::Number, return_value);
	}

	data divide(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		auto arguments = utils::parse_arguments(inputs, 2);
		if (!utils::all_types_are(arguments, data_type::Number))
			throw xig::error(xig::error_types::invalid_arguments, "Not A Number", function_call_list);

		long double return_value = arguments.at(0).number();
		for (unsigned int i(1); i < arguments.size(); i++)
		{
			return_value /= arguments.at(i).number();
		}

		return data(data_type::Number, return_value);
	}

}}