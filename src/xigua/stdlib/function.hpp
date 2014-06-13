#pragma once

#include <vector>
#include <functional>
#include <numeric>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"
#include "xigua/evaluate.hpp"
#include "xigua/parser.hpp"

#include "xigua/stdlib/utils.hpp"

namespace xig {
namespace stdlib {

void traverseProcess(data process, std::function<void(data&)> fn) {
	if (process.type() != data_type::process) return;
	auto p = process.as_process();
	for (auto &i : p) {
		if (i.type() == data_type::process)
			traverseProcess(i, fn);
		else
			fn(i);
	}
}

struct WrappedFunction : public method {
public:
	WrappedFunction(int amount_of_args, bool process_args, std::vector<data> args, data proc, enviroment new_env)
		: amount_of_args(amount_of_args), process_args(process_args), args(args), proc(proc), new_env(new_env) {}

	int amount_of_arguments() const { return amount_of_args; }
	bool has_process_arguments() const { return process_args; }

	bool process_arguments_pass(std::vector<data> fn_args, enviroment &fn_env, std::vector<std::string> fn_fcl) {
		if (!process_args) return true;
        bool ret = true;
        process_arguments(fn_args, fn_env, [&](data &val){
            auto result = evaluate(new_env, val, fn_fcl);
            if (result.type() != data_type::boolean || !result.as_boolean()){
                ret = false;
            }
        });
		return ret;
	}


	data run(std::vector<data> fn_args, enviroment &fn_env,	std::vector<std::string> fn_fcl) {
        process_arguments(fn_args, fn_env);
		return evaluate(new_env, proc, fn_fcl);
	}

private:
    void process_arguments(std::vector<data> fn_args, enviroment &fn_env, std::function<void(data&)> handle_process = {}) {
        short missing = 0;
        for (unsigned int i(0); i < args.size(); ++i) {
            if (args.at(i).type() == data_type::process) {
                traverseProcess(args.at(i), [&](data &traversed){
                    if (traversed.type() == data_type::symbol) {
                        bool found_in_self = (new_env.find(traversed.as_symbol(), true) != nullptr);
                        bool found_anywhere = (new_env.find(traversed.as_symbol()) != nullptr);
                        
                        if ((!found_anywhere) || !(found_anywhere && !found_in_self))  {
                            new_env.set(traversed.as_symbol(), fn_args.at(i - missing));
                            missing--;
                        }
                    }
                });
                handle_process(args.at(i));
            } else if (args.at(i).as_symbol() != "&") {
                new_env.set(args.at(i).as_symbol(), fn_args.at(i - missing));
            } else {
                missing++;
            }
        }
    }
    
private:
	int amount_of_args;
	bool process_args;
	std::vector<data> args;
	data proc;
	enviroment new_env;

};


class create_lambda : public method {
  int amount_of_arguments() const { return 2; }
  bool should_evaluate_arguments() const { return false; }
  bool has_repeating_arguments() const { return true; }

  data run(std::vector<data> args, enviroment &env, std::vector<std::string> fcl) {
    
	auto arguments = utils::parse_arguments(args, 2);
    enviroment new_env(env_type::function, &env);
    function return_fn;

    for (int argument(0); argument < arguments.size(); argument += 2) {
      bool repeating = false;
	  bool process_args = false;

      for (auto arg : arguments.at(argument).as_tuple()) {
		  if (arg.type() == data_type::process) {
			  process_args = true;
		  } else if (arg.type() != data_type::symbol) {
			  throw error(error_type::invalid_arguments, "Not A Symbol Or Process In Tuple", fcl);
		  } else if (arg.as_symbol() == "&") {
			  repeating = true;
		  }
      }

      int amount_of_args = arguments.at(argument).as_tuple().size() - (int)repeating;

	  auto return_function = WrappedFunction(amount_of_args, process_args, arguments.at(argument).as_tuple(), arguments.at(argument + 1), new_env);

      return_fn.add_method(return_function);
    }
    return data(data_type::function, return_fn);
  }
};

}
}
