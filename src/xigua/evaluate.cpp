#include "xigua/evaluate.hpp"

namespace xig {

	data evaluate(enviroment & env, data input_data, std::vector<std::string> function_call_list) {

		if (input_data.type() == data_type::symbol)
		{
			auto sym = input_data.as_symbol();
			data * symbol_value = env.find(input_data.as_symbol());
			if (symbol_value == nullptr) {
				throw xig::error(xig::error_types::invalid_arguments, "Cannot Find Symbol: " + input_data.as_symbol(), function_call_list);
			}
			return *symbol_value;
		}
		else if (input_data.type() == data_type::number)
		{
			return input_data;
		}
		else if (input_data.type() == data_type::function)
		{
			return input_data;
		}
		else if (input_data.type() == data_type::keyword)
		{
			return input_data;
		}
		else if (input_data.type() == data_type::string)
		{
			return input_data;
		}
		else if (input_data.type() == data_type::boolean)
		{
			return input_data;
		}
		else if (input_data.type() == data_type::process)
		{
			if (input_data.as_process().size() == 0) throw error(error_types::parsing_error, "No Data In Process", {});

			if (input_data.as_process().at(0).type() == data_type::process || input_data.as_process().at(0).type() == data_type::symbol)
			{
				if (input_data.as_process().at(0).type() == data_type::symbol)
				{
					function_call_list.push_back(input_data.as_process().at(0).as_symbol());
				}

				std::vector<data> new_proc_data = input_data.as_process();
				new_proc_data.at(0) = evaluate(env, input_data.as_process().at(0), function_call_list);
				input_data = data(data_type::process, new_proc_data);
			}

			if (input_data.as_process().size() == 0)
			{
				return data(data_type::none);
			}
			else if (input_data.as_process().at(0).type() == data_type::function)
			{
				auto process_copy = input_data.as_process();
				auto firstElement = process_copy.begin() + 1;
				auto lastElement = process_copy.end();
				std::vector<data> functionArgs(firstElement, lastElement);

				return input_data.as_process().at(0).as_function().call(functionArgs, env, function_call_list);
			}
			else
			{
				data return_value = data(data_type::none);
				for (data item : input_data.as_process())
					return_value = evaluate(env, item, function_call_list);
				return return_value;
			}
		}
		else if (input_data.type() == data_type::tuple)
		{
			std::vector<data> new_tuple_data;
			for (auto data : input_data.as_tuple())
			{
				new_tuple_data.push_back(evaluate(env, data, function_call_list));
			}
			return data(data_type::tuple, new_tuple_data);
		}
		else if (input_data.type() == data_type::map)
		{
			std::map<data, data> new_tuple_data;
			for (auto data : input_data.as_map())
			{
				auto first = data.first;
				auto second = data.second;
				new_tuple_data[evaluate(env, first, function_call_list)] = evaluate(env, second, function_call_list);
			}
			return data(data_type::map, new_tuple_data);
		}

		return data(data_type::none);
	}

}
