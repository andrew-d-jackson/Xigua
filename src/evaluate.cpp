#include "evaluate.hpp"

namespace xig {

	data evaluate(enviroment & env, data input_data, std::vector<std::string> function_call_list) {

		if (input_data.type() == data_type::Symbol)
		{
			data * symbol_value = env.find(input_data.symbol());
			if (symbol_value == nullptr) {
				throw xig::error(xig::error_types::invalid_arguments, "Cannot Find Symbol", function_call_list);
			}
			return *symbol_value;
		}
		else if (input_data.type() == data_type::Number)
		{
			return input_data;
		}
		else if (input_data.type() == data_type::Function)
		{
			return input_data;
		}
		else if (input_data.type() == data_type::String)
		{
			return input_data;
		}
		else if (input_data.type() == data_type::Bool)
		{
			return input_data;
		}
		else if (input_data.type() == data_type::Proc)
		{
			if (input_data.proc().at(0).type() == data_type::Proc || input_data.proc().at(0).type() == data_type::Symbol)
			{
				if (input_data.proc().at(0).type() == data_type::Symbol)
				{
					function_call_list.push_back(input_data.proc().at(0).symbol());
				}

				std::vector<data> new_proc_data = input_data.proc();
				new_proc_data.at(0) = evaluate(env, input_data.proc().at(0), function_call_list);
				input_data.proc(new_proc_data);
			}

			if (input_data.proc().size() == 0)
			{
				return data(data_type::None);
			}
			else if (input_data.proc().at(0).type() == data_type::Function)
			{
				auto process_copy = input_data.proc();
				auto firstElement = process_copy.begin() + 1;
				auto lastElement = process_copy.end();
				std::vector<data> functionArgs(firstElement, lastElement);

				return input_data.proc().at(0).functions().call(functionArgs, env, function_call_list);
			}
			else
			{
				data return_value = data(data_type::None);
				for (data item : input_data.proc())
					return_value = evaluate(env, item, function_call_list);
				return return_value;
			}
		}
		else if (input_data.type() == data_type::Tuple)
		{
			std::vector<data> new_tuple_data;
			for (auto data : input_data.tuple())
			{
				new_tuple_data.push_back(evaluate(env, data, function_call_list));
			}
			return data(data_type::Tuple, new_tuple_data);
		}
		else if (input_data.type() == data_type::HashMap)
		{
			std::map<data, data> new_tuple_data;
			for (auto data : input_data.hash_map())
			{
				auto first = data.first;
				auto second = data.second;
				new_tuple_data[evaluate(env, first, function_call_list)] = evaluate(env, second, function_call_list);
			}
			return data(data_type::HashMap, new_tuple_data);
		}

		return data(data_type::None);
	}

}
