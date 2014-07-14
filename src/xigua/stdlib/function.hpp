#pragma once

#include <vector>
#include <set>
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

struct WrappedFunction : public method {
public:
  WrappedFunction(int amount_of_args, bool process_args, std::vector<data> args,
                  data proc, enviroment new_env)
      : amount_of_args(amount_of_args), process_args(process_args), args(args),
        proc(proc), new_env(new_env) {}

  int amount_of_arguments() const { return amount_of_args; }
  bool has_process_arguments() const { return process_args; }

  bool process_arguments_pass(call_info fn_fci) {
    if (!process_args)
      return true;
    bool ret = true;
    process_arguments(fn_fci.args, fn_fci.env, [&](data &val) {
      auto result = evaluate(new_env, val, fn_fci.debug);
      if (result.type() != data_type::boolean || !result.as_boolean()) {
        ret = false;
      }
    });
    return ret;
  }

  data run(call_info fn_fci) {
    process_arguments(fn_fci.args, fn_fci.env);
    return evaluate(new_env, proc, fn_fci.debug);
  }

private:
  void process_arguments(std::vector<data> fn_args, enviroment &fn_env) {
    process_arguments(fn_args, fn_env, [](data &val) {});
  }

  void process_arguments(std::vector<data> fn_args, enviroment &fn_env,
                         std::function<void(data &)> handle_process) {
    short current_arg = 0;
    auto vars = std::set<std::string>();

    for (unsigned int i(0); i < args.size(); ++i) {
      if (args.at(i).type() == data_type::process) {
        traverseProcess(args.at(i), [&](data &traversed) {
          if (traversed.type() == data_type::symbol) {
            bool found_in_self =
                (new_env.find(traversed.as_symbol(), true) != nullptr);
            bool found_anywhere =
                (new_env.find(traversed.as_symbol()) != nullptr);
            bool in_vars = (vars.find(traversed.as_symbol()) != vars.end());

            if (((!found_anywhere) || !(found_anywhere && !found_in_self)) &&
                !in_vars) {
              new_env.set(traversed.as_symbol(), fn_args.at(current_arg));
              vars.insert(traversed.as_symbol());
              current_arg++;
            }
          }
        });
        handle_process(args.at(i));
      } else if (args.at(i).type() == data_type::symbol) {
        if (args.at(i).as_symbol() != "&") {
          bool in_vars = (vars.find(args.at(i).as_symbol()) != vars.end());
          if (!in_vars) {
            new_env.set(args.at(i).as_symbol(), fn_args.at(current_arg));
            current_arg++;
          } else {
            vars.insert(args.at(i).as_symbol());
          }
        }
      } else {
        auto b = make_boolean(args.at(i) == fn_args.at(i));
        handle_process(b);
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

class create_lambda : public method {
  int amount_of_arguments() const { return 2; }
  bool should_evaluate_arguments() const { return false; }
  bool has_repeating_arguments() const { return true; }

  data run(call_info fci) {

    auto arguments = utils::parse_arguments(fci.args, 2);
    enviroment new_env(env_type::function, &fci.env);
    function return_fn;

    for (int argument(0); argument < arguments.size(); argument += 2) {
      bool repeating = false;
      bool process_args = false;

      for (auto arg : arguments.at(argument).as_tuple()) {
        if (arg.type() == data_type::symbol) {
          if (arg.as_symbol() == "&")
            repeating = true;
        } else {
          process_args = true;
        }
      }

      int amount_of_args =
          get_amount_of_args(arguments.at(argument).as_tuple(), new_env);

      auto return_function = WrappedFunction(
          amount_of_args, process_args, arguments.at(argument).as_tuple(),
          arguments.at(argument + 1), new_env);

      return_fn.add_method(return_function);
    }
    return data(return_fn);
  }
};
}
}
