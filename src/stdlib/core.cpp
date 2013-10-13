#include "core.hpp"

namespace xig {
namespace stdlib {

	data define(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		execution_enviroment->set(inputs.at(0).string(), evaluate(*execution_enviroment, inputs.at(1), function_call_list));
		return data(data_type::None);
	}

	data create_lambda(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		enviroment nenv(env_type::Function, execution_enviroment);

		bool repeating = false;

		for (auto item : inputs.at(0).tuple())
		{
			if (item.type() != data_type::Symbol) {
				std::cout << "non-symbol passed as function argument name" << std::endl;
				exit(1);
			} else if (item.symbol() == "&") {
				repeating = true;
			}
		}

		xigua_lambda_t fn = [nenv, inputs](std::vector<data> fn_inputs, enviroment* fn_enviroment, std::vector<std::string> function_call_list)mutable->data
		{
			short missing = 0;
			for (unsigned int i(0); i < inputs.at(0).tuple().size(); ++i)
			{
				if (inputs.at(0).tuple().at(i).symbol() != "&") {
					nenv.set(inputs.at(0).tuple().at(i).symbol(), fn_inputs.at(i-missing));
				} else {
					missing = 1;
				}
			}

			return evaluate(nenv, inputs.at(1), function_call_list);
		};

		data return_data(data_type::Function, function(method(inputs.at(0).tuple().size()-((int)repeating*2), repeating, fn)));

		return return_data;
	}

	data let_expression(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		if (inputs.at(0).type() != data_type::HashMap)
			throw xig::error(xig::error_types::invalid_arguments, "Not A HashMap", function_call_list);

		if (inputs.at(1).type() != data_type::Proc)
			throw xig::error(xig::error_types::invalid_arguments, "Not A Process", function_call_list);


		enviroment container_enviroment(env_type::Let, execution_enviroment);
		for (auto map_pair : inputs.at(0).hash_map()) {

			if (map_pair.first.type() != data_type::Symbol)
				throw xig::error(xig::error_types::invalid_arguments, "Not A Symbol", function_call_list);

			container_enviroment.set(map_pair.first.symbol(), evaluate(container_enviroment, map_pair.second, function_call_list), true);
		}

		return evaluate(container_enviroment, inputs.at(1), function_call_list);
	}

	data if_expression(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		if (evaluate(*execution_enviroment, inputs.at(0)).boolean())
			return evaluate(*execution_enviroment, inputs.at(1), function_call_list);
		else
			return evaluate(*execution_enviroment, inputs.at(2), function_call_list);
	}

	data print_line(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		std::cout << inputs.at(0).as_string() << std::endl;
		return data(data_type::None);
	}

	data get_input(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		std::string str;
		std::cin >> str;
		return data(data_type::String, str);
	}

	data map(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		auto arguments = utils::parse_arguments(inputs, 2);

		if (arguments.size() > 2) {
			int tuple_sizes = arguments.at(0).tuple().size();
			for (unsigned int i(1); i < arguments.size() - 1; i++)	{
				if (arguments.at(i).tuple().size() != tuple_sizes)
					throw xig::error(xig::error_types::invalid_arguments, "Tuple Lengths Are Different", function_call_list);
			}
		}

		std::vector<data> return_values;

		for (unsigned int i(0); i < arguments.at(1).tuple().size(); i++)
		{
			std::vector<data> temp_proc = { arguments.at(arguments.size()-1) };
			for (unsigned int j(0); j < arguments.size() - 1; j++)
				temp_proc.push_back(arguments.at(j).tuple().at(i));

			data temp_function(data_type::Proc, temp_proc);
			return_values.push_back(evaluate(*execution_enviroment, temp_function, function_call_list));
		}

		return data(data_type::Tuple, return_values);
	}

	data apply(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		if (inputs.at(0).type() != data_type::Tuple)
			throw xig::error(xig::error_types::invalid_arguments, "Not A Tuple", function_call_list);

		if (inputs.at(1).type() != data_type::Function)
			throw xig::error(xig::error_types::invalid_arguments, "Not A Function", function_call_list);

		std::vector<data> temp_proc = { inputs.at(1) };

		for (auto data : inputs.at(0).tuple())
			temp_proc.push_back(data);

		data temp_function(data_type::Proc, temp_proc);
		return evaluate(*execution_enviroment, temp_function, function_call_list);
	}

	data partial(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		if (inputs.at(0).type() != data_type::Function)
			throw xig::error(xig::error_types::invalid_arguments, "Not A Function", function_call_list);

		auto arguments = utils::parse_arguments(inputs, 2);
		
		data captured_function = arguments.at(0);
		std::vector<data> captured_function_args(arguments.begin()+1, arguments.end());

		xigua_lambda_t fn = [captured_function, captured_function_args](std::vector<data> fn_inputs, enviroment* fn_enviroment, std::vector<std::string> fn_function_call_list)mutable -> data
		{
			auto fn_arguments = utils::parse_arguments(fn_inputs, 0);
			
			captured_function_args.insert(captured_function_args.end(), fn_arguments.begin(), fn_arguments.end());
			return captured_function.functions().call(captured_function_args, fn_enviroment, fn_function_call_list);
		};

		data return_function(data_type::Function, function(method(0, true, fn)));
		return return_function;
	}

}}