#pragma once

#include <vector>
#include <functional>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"
#include "xigua/evaluate.hpp"

#include "xigua/stdlib/utils.hpp"

namespace xig {
namespace stdlib {

	class define : public method {
		int amount_of_arguments() const { return 2; }
		bool should_evaluate_arguments() const { return false; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			env.set(args.at(0).as_string(), evaluate(env, args.at(1), fcl));
			return data(data_type::none);
		}
	};

	class create_lambda : public method {
		int amount_of_arguments() const { return 2; }
		bool should_evaluate_arguments() const { return false; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			enviroment new_env(env_type::function, &env);

			bool repeating = false;
			for (auto arg : args.at(0).as_tuple()) {
				if (arg.type() != data_type::symbol) {
					throw error(error_types::invalid_arguments, "Not A Symbol In Tuple", fcl);
				}
				else if (arg.as_symbol() == "&") {
					repeating = true;
				}
			}
			int amount_of_args = args.at(0).as_tuple().size() - (int)repeating;

			struct fn : public method {
				int _amount_of_args;
				std::vector<data> _args;
				enviroment _new_env;

				fn(int amount_of_args, std::vector<data> args, enviroment new_env)
						: _amount_of_args(amount_of_args),
						  _args(args),
						  _new_env(new_env){}

				int amount_of_arguments() const { return _amount_of_args; }

				data run(std::vector<data> fn_args, enviroment & fn_env, std::vector<std::string> fn_fcl) {
					short missing = 0;
					for (unsigned int i(0); i < _args.at(0).as_tuple().size(); ++i){
						if (_args.at(0).as_tuple().at(i).as_symbol() != "&") {
							_new_env.set(_args.at(0).as_tuple().at(i).as_symbol(), fn_args.at(i - missing));
						} else {
							missing = 1;
						}
					}
					return evaluate(_new_env, _args.at(1), fn_fcl);
				}

			} return_function = { amount_of_args, args, new_env };

			data return_data(data_type::function, function(return_function));

			return return_data;
		};
	};

	class if_expression : public method {
		int amount_of_arguments() const { return 3; }
		bool should_evaluate_arguments() const { return false; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			if (evaluate(env, args.at(0), fcl).as_boolean())
				return evaluate(env, args.at(1), fcl);
			else
				return evaluate(env, args.at(2), fcl);
		}
	};

	class let_expression : public method {
		int amount_of_arguments() const { return 2; }
		bool should_evaluate_arguments() const { return false; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			if (args.at(0).type() != data_type::map)
				throw error(error_types::invalid_arguments, "Not A HashMap", fcl);

			if (args.at(1).type() != data_type::process)
				throw error(error_types::invalid_arguments, "Not A Process", fcl);


			enviroment container_enviroment(env_type::let, &env);
			for (auto map_pair : args.at(0).as_map()) {
				if (map_pair.first.type() != data_type::symbol)
					throw xig::error(xig::error_types::invalid_arguments, "Not A Symbol", fcl);

				container_enviroment.set(map_pair.first.as_symbol(), evaluate(container_enviroment, map_pair.second, fcl), true);
			}

			return evaluate(container_enviroment, args.at(1), fcl);
		}
	};

	class get_input : public method {
		int amount_of_arguments() const { return 0; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			std::string str;
			std::cin >> str;
			return data(data_type::string, str);
		}
	};

	class print_line : public method {
		int amount_of_arguments() const { return 1; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			std::cout << string_representation(args.at(0)) << std::endl;
			return data(data_type::none);
		}
	};

	class map : public method {
		int amount_of_arguments() const { return 2; }
		bool has_repeating_arguments() const { return true; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			auto arguments = utils::parse_arguments(args, 2);

			if (arguments.size() > 2) {
				unsigned tuple_sizes = arguments.at(0).as_tuple().size();
				for (unsigned int i(1); i < arguments.size() - 1; i++)	{
					if (arguments.at(i).as_tuple().size() != tuple_sizes)
						throw error(error_types::invalid_arguments, "Tuple Lengths Are Different", fcl);
				}
			}

			std::vector<data> return_values;
			for (unsigned int i(0); i < arguments.at(1).as_tuple().size(); i++) {
				std::vector<data> temp_proc = { arguments.at(arguments.size()-1) };
				for (unsigned int j(0); j < arguments.size() - 1; j++)
					temp_proc.push_back(arguments.at(j).as_tuple().at(i));

				data temp_function(data_type::process, temp_proc);
				return_values.push_back(evaluate(env, temp_function, fcl));
			}

			return data(data_type::tuple, return_values);
		}
	};


	class apply : public method {
		int amount_of_arguments() const { return 2; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			if (args.at(0).type() != data_type::function)
				throw error(error_types::invalid_arguments, "Not A Function", fcl);

			if (args.at(1).type() != data_type::tuple)
				throw error(error_types::invalid_arguments, "Not A Tuple", fcl);

			std::vector<data> temp_proc = { args.at(0) };

			for (auto data : args.at(1).as_tuple())
				temp_proc.push_back(data);

			data temp_function(data_type::process, temp_proc);
			return evaluate(env, temp_function, fcl);
		}
	};


	class partial : public method {
		int amount_of_arguments() const { return 2; }
		bool has_repeating_arguments() const { return true; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			if (args.at(0).type() != data_type::function)
				throw error(error_types::invalid_arguments, "Not A Function", fcl);

			auto arguments = utils::parse_arguments(args, 2);
			
			data captured_function = arguments.at(0);
			std::vector<data> captured_function_args(arguments.begin()+1, arguments.end());

			struct fn : public method {
				data _captured_function;
				std::vector<data> _captured_function_args;

				fn(data func, std::vector<data> args)
					: _captured_function(func),	 _captured_function_args(args) {}

				int amount_of_arguments() const { return 0; }
				bool has_repeating_arguments() const { return true; }

				data run(std::vector<data> fn_args, enviroment & fn_env, std::vector<std::string> fn_fcl) {
					auto fn_arguments = utils::parse_arguments(fn_args, 0);
					std::vector<data> final_args = _captured_function_args;
					final_args.insert(final_args.end(), fn_arguments.begin(), fn_arguments.end());
					return _captured_function.as_function().call(final_args, fn_env, fn_fcl);
				}
			} return_method = {captured_function, captured_function_args};

			data return_function(data_type::function, function(return_method));
			return return_function;
		}
	};

	class macro : public method {
		int amount_of_arguments() const { return 2; }
		bool should_evaluate_arguments() const { return false; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			if (args.at(0).type() != data_type::tuple)
				throw error(error_types::invalid_arguments, "Not A Tuple", fcl);

			if (args.at(1).type() != data_type::process)
				throw error(error_types::invalid_arguments, "Not A Process", fcl);

			for (const auto &i: args.at(0).as_tuple()) {
				if (i.type() != data_type::symbol)
					throw error(error_types::invalid_arguments, "Not A Symbol", fcl);
			}

			struct fn : public method {
				const data _captured_proc;
				const std::vector<data> _captured_proc_args;

				fn(data func, std::vector<data> args)
					: _captured_proc(func),	 _captured_proc_args(args) {}

				int amount_of_arguments() const { return _captured_proc_args.size(); }
				bool has_repeating_arguments() const { return false; }
				bool should_evaluate_arguments() const { return false; }

				std::vector<data> replace(std::vector<data> list, const std::vector<data> &rp) {
					for(auto &i: list) {
						if (i.type() == data_type::tuple) {
							i = make_tuple(replace(i.as_tuple(), rp));
						} else if (i.type() == data_type::process) {
							i = make_process(replace(i.as_process(), rp));
						} else if (i.type() == data_type::symbol){
							for(unsigned keyword_i(0); keyword_i < _captured_proc_args.size(); keyword_i++) {
								if (_captured_proc_args.at(keyword_i).as_symbol() == i.as_symbol()) {
									i = rp.at(keyword_i);
									break;
								}
							}
						}
					}
					return list;
				}

				data run(std::vector<data> fn_args, enviroment & fn_env, std::vector<std::string> fn_fcl) {
					auto new_proc = replace(_captured_proc.as_process(), fn_args);
					return evaluate(fn_env, make_process(new_proc), fn_fcl);
				}
			} return_method = {args.at(1), args.at(0).as_tuple()};

			data return_function(data_type::function, function(return_method));
			return return_function;
		}
	};

}}