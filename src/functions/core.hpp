#pragma once

#include <vector>
#include <string>
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
		namespace Core
		{

			data define(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				enviroment->set(inputs.at(0).string(), inputs.at(1).evaluate(enviroment, function_call_list));
				return data(data_type::None);
			}

			data create_lambda(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				Enviroment nenv(EnvTypes::Function, enviroment);
				data return_data(data_type::Function);

				int repeating = 0;

				for (auto item : inputs.at(0).tuple())
				{
					if (item.type() != data_type::Symbol) {
						std::cout << "non-symbol passed as function argument name" << std::endl;
						exit(1);
					} else if (item.symbol() == "&") {
						repeating = 1;
					}
				}

				xigua_lambda_t fn = [nenv, inputs](std::vector<data> fn_inputs, Enviroment* fn_enviroment, std::vector<std::string> function_call_list)mutable->data
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

					return inputs.at(1).evaluate(&nenv, function_call_list);
				};

				return_data.set_function(fn, inputs.at(0).tuple().size()-(repeating*2), repeating, true);

				return return_data;
			}

			data let_expression(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				if (inputs.at(0).type() != data_type::HashMap)
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A HashMap", function_call_list);

				if (inputs.at(1).type() != data_type::Proc)
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Process", function_call_list);


				Enviroment container_enviroment(EnvTypes::Let, enviroment);
				for (auto map_pair : inputs.at(0).hash_map()) {

					if (map_pair.first.type() != data_type::Symbol)
						throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Symbol", function_call_list);

					container_enviroment.set(map_pair.first.symbol(), map_pair.second.evaluate(&container_enviroment, function_call_list), true);
				}

				return inputs.at(1).evaluate(&container_enviroment, function_call_list);
			}

			data if_expression(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				if (inputs.at(0).evaluate(enviroment).boolean())
					return inputs.at(1).evaluate(enviroment, function_call_list);
				else
					return inputs.at(2).evaluate(enviroment, function_call_list);
			}

			data print_line(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				std::cout << inputs.at(0).as_string() << std::endl;
				return data(data_type::None);
			}

			data get_input(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				std::string str;
				std::cin >> str;
				return data(data_type::String, str);
			}

			data map(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				auto arguments = xig::FunctionUtils::parse_arguments(inputs, 2);

				if (arguments.size() > 2) {
					int tuple_sizes = arguments.at(0).tuple().size();
					for (unsigned int i(1); i < arguments.size() - 1; i++)	{
						if (arguments.at(i).tuple().size() != tuple_sizes)
							throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Tuple Lengths Are Different", function_call_list);
					}
				}

				std::vector<data> return_values;

				for (unsigned int i(0); i < arguments.at(1).tuple().size(); i++)
				{
					std::vector<data> temp_proc = { arguments.at(arguments.size()-1) };
					for (unsigned int j(0); j < arguments.size() - 1; j++)
						temp_proc.push_back(arguments.at(j).tuple().at(i));

					data temp_function(data_type::Proc, temp_proc);
					return_values.push_back(temp_function.evaluate(enviroment, function_call_list));
				}

				return data(data_type::Tuple, return_values);
			}

			data apply(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				if (inputs.at(0).type() != data_type::Tuple)
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Tuple", function_call_list);

				if (inputs.at(1).type() != data_type::Function)
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Function", function_call_list);

				std::vector<data> temp_proc = { inputs.at(1) };

				for (auto data : inputs.at(0).tuple())
					temp_proc.push_back(data);

				data temp_function(data_type::Proc, temp_proc);
				return temp_function.evaluate(enviroment, function_call_list);
			}

			data partial(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				if (inputs.at(0).type() != data_type::Function)
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Function", function_call_list);

				auto arguments = xig::FunctionUtils::parse_arguments(inputs, 2);
				
				data captured_function = arguments.at(0);
				std::vector<data> captured_function_args(arguments.begin()+1, arguments.end());

				xigua_lambda_t fn = [captured_function, captured_function_args](std::vector<data> fn_inputs, Enviroment* fn_enviroment, std::vector<std::string> fn_function_call_list)mutable -> data
				{
					auto fn_arguments = xig::FunctionUtils::parse_arguments(fn_inputs, 0);
					
					captured_function_args.insert(captured_function_args.end(), fn_arguments.begin(), fn_arguments.end());
					return captured_function.call_function(captured_function_args, fn_enviroment, fn_function_call_list);
				};

				data return_function(data_type::Function);
				return_function.set_function(fn, 0, 1, true);
				return return_function;
			}

		}
	}
}