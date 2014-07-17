#pragma once

#include <vector>
#include <set>
#include <functional>
#include <numeric>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"
#include "xigua/evaluate.hpp"
#include "xigua/stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class create_lambda : public method {
  int amount_of_arguments() const { return 2; }
  bool should_evaluate_arguments() const { return false; }
  bool has_repeating_arguments() const { return true; }

  data run(call_info fci);
};

class wrapped_function : public method {
public:
  wrapped_function(int amount_of_args, bool has_repeating_args,
                   bool has_proc_args, std::vector<data> parameters, data proc,
                   enviroment env)
      : amount_of_args(amount_of_args), has_repeating_args(has_repeating_args),
        has_proc_args(has_proc_args), parameters(parameters), proc(proc),
        env(env) {}

  int amount_of_arguments() const { return amount_of_args; }
  bool has_process_arguments() const { return has_proc_args; }
  bool has_repeating_arguments() const { return has_repeating_args; }

  bool process_arguments_pass(call_info fci);
  data run(call_info fci);

private:
  int amount_of_args;
  bool has_repeating_args;
  bool has_proc_args;

  std::vector<data> parameters;
  data proc;
  enviroment env;
};

void traverseProcess(data process, std::function<void(data &)> fn) {
  if (process.type() != data_type::process)
    return;
  auto p = process.as_process();
  for (auto &i : p) {
    if (i.type() == data_type::process)
      traverseProcess(i, fn);
    else
      fn(i);
  }
}

void assign_process_to_env(const data &current_param,
                           std::vector<data>::const_iterator &current_arg,
                           enviroment &env, std::set<std::string> vars) {
  traverseProcess(current_param, [&](data &traversed) {
    if (traversed.type() == data_type::symbol) {
      bool found_in_self = (env.find(traversed.as_symbol(), true) != nullptr);
      bool found_anywhere = (env.find(traversed.as_symbol()) != nullptr);
      bool in_vars = (vars.find(traversed.as_symbol()) != vars.end());

      if (((!found_anywhere) || !(found_anywhere && !found_in_self)) &&
          !in_vars) {
        env.set(traversed.as_symbol(), *current_arg);
        vars.insert(traversed.as_symbol());
        ++current_arg;
      }
    }
  });
}

void assign_symbol_to_env(const data &current_param,
                          std::vector<data>::const_iterator &current_arg,
                          enviroment &env, std::set<std::string> vars) {
  if (current_param.as_symbol() != "&") {
    bool in_vars = (vars.find(current_param.as_symbol()) != vars.end());
    if (!in_vars) {
      env.set(current_param.as_symbol(), *current_arg);
      vars.insert(current_param.as_symbol());
      current_arg++;
    }
  }
}

void assign_args_to_env(const std::vector<data> &params,
                        const std::vector<data> &args, enviroment &env) {
  auto current_arg = args.begin();
  auto vars = std::set<std::string>();

  for (auto current_param = params.begin(); current_param != params.end();
       ++current_param) {
    switch (current_param->type()) {
    case data_type::process:
      assign_process_to_env(*current_param, current_arg, env, vars);
      break;
    case data_type::symbol:
      assign_symbol_to_env(*current_param, current_arg, env, vars);
      break;
    default:
      break;
    }
  }
}

bool process_args_pass(const std::vector<data> &params,
                       const std::vector<data> &args, enviroment &env,
                       debug_info debug) {
  auto current_arg = args.begin();
  auto vars = std::set<std::string>();

  for (auto current_param = params.begin(); current_param != params.end();
       ++current_param) {
    switch (current_param->type()) {
    case data_type::process: {
      assign_process_to_env(*current_param, current_arg, env, vars);
      auto result = evaluate(env, *current_param, debug);
      if (result.type() != data_type::boolean || !result.as_boolean()) {
        return false;
      }
      break;
    }
    case data_type::symbol:
      break;
    default:
      if (*current_param != evaluate(env, *current_arg))
        return false;
      break;
    }
  }
  return true;
}

int get_amount_of_args(std::vector<data> args, enviroment &env) {
  short amount = 0;
  auto vars = std::set<std::string>();

  for (unsigned int i(0); i < args.size(); ++i) {
    if (args.at(i).type() == data_type::process) {
      traverseProcess(args.at(i), [&](data &traversed) {
        if (traversed.type() == data_type::symbol) {
          bool found = (env.find(traversed.as_symbol()) != nullptr);
          bool in_vars = (vars.find(traversed.as_symbol()) != vars.end());
          if (!found && !in_vars) {
            vars.insert(traversed.as_symbol());
            amount++;
          }
        }
      });
    } else if (args.at(i).type() == data_type::symbol) {
      if (args.at(i).as_symbol() != "&") {
        bool in_vars = (vars.find(args.at(i).as_symbol()) != vars.end());
        if (!in_vars) {
          amount++;
        } else {
          vars.insert(args.at(i).as_symbol());
        }
      }
    } else {
      amount++;
    }
  }
  return amount;
}

bool wrapped_function::process_arguments_pass(call_info fci) {

  if (!has_proc_args)
    return true;
  auto execute_env = env;
  return process_args_pass(parameters, fci.args, execute_env, fci.debug);
}

data wrapped_function::run(call_info fci) {
  auto execute_env = env;
  assign_args_to_env(parameters, fci.args, execute_env);
  return evaluate(execute_env, proc, fci.debug);
}

data create_lambda::run(call_info fci) {
  auto arguments = utils::parse_arguments(fci.args, 2);
  function return_fn;

  for (int argument(0); argument < arguments.size(); argument += 2) {
    bool repeating = false;
    bool process_args = false;
    enviroment fn_env(env_type::function, &fci.env);

    for (auto arg : arguments.at(argument).as_tuple()) {
      if (arg.type() == data_type::symbol) {
        if (arg.as_symbol() == "&")
          repeating = true;
      } else {
        process_args = true;
      }
    }

    int amount_of_args =
        get_amount_of_args(arguments.at(argument).as_tuple(), fn_env);

    auto return_function = wrapped_function(
        amount_of_args, repeating, process_args,
        arguments.at(argument).as_tuple(), arguments.at(argument + 1), fn_env);

    return_fn.add_method(return_function);
  }
  return data(return_fn);
}
}
}
