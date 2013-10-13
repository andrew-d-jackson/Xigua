#include "tuple.hpp"


namespace xig {
namespace stdlib {

	data join(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		auto arguments = utils::parse_arguments(inputs, 2);

		std::vector<data> return_value;
		for (auto argument : arguments)
		{
			if (argument.type() == data_type::Tuple) {
				for (auto element : argument.tuple())
					return_value.push_back(element);
			} else {
				return_value.push_back(argument);
			}
		}

		return data(data_type::Tuple, return_value);
	}

	data unique(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		if (inputs.at(0).type() != data_type::Tuple)
			throw xig::error(xig::error_types::invalid_arguments, "Not A Tuple", function_call_list);

		auto initial_tuple = inputs.at(0).tuple();
		std::sort(initial_tuple.begin(), initial_tuple.end());
		auto unique_iterator = std::unique(initial_tuple.begin(), initial_tuple.end());
		std::vector<data> return_value(initial_tuple.begin(), unique_iterator);

		return data(data_type::Tuple, return_value);
	}

	data first(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		if (inputs.at(0).type() != data_type::Tuple)
			throw xig::error(xig::error_types::invalid_arguments, "Not A Tuple", function_call_list);

		if (inputs.at(0).tuple().size() < 1)
			throw xig::error(xig::error_types::invalid_arguments, "Not In Range", function_call_list);

		return inputs.at(0).tuple().at(0);
	}

	data last(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		if (inputs.at(0).type() != data_type::Tuple)
			throw xig::error(xig::error_types::invalid_arguments, "Not A Tuple", function_call_list);

		if (inputs.at(0).tuple().size() < 1)
			throw xig::error(xig::error_types::invalid_arguments, "Not In Range", function_call_list);

		return inputs.at(0).tuple().at(inputs.at(0).tuple().size()-1);
	}

	data range(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		if (!utils::all_types_are(inputs, data_type::Number))
			throw xig::error(xig::error_types::invalid_arguments, "Not A Number", function_call_list);

		long double start = inputs.at(0).number();
		long double end = inputs.at(1).number();
		long double step = inputs.at(2).number();

		if (start > end && step >= 0)
			throw xig::error(xig::error_types::invalid_arguments, "Range Invalid", function_call_list);
		else if (start < end && step <= 0)
			throw xig::error(xig::error_types::invalid_arguments, "Range Invalid", function_call_list);
		else if (step == 0 || start == end)
			throw xig::error(xig::error_types::invalid_arguments, "Range Invalid", function_call_list);


		std::vector<data> return_value;

		if (start > end) {
			while (start > end) {
				return_value.push_back(data(data_type::Number, start));
				start += step;
			}
		} else if (start < end) {
			while (start < end) {
				return_value.push_back(data(data_type::Number, start));
				start += step;
			}
		}

		return data(data_type::Tuple, return_value);
	}


}}