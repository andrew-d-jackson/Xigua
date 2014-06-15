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

class define : public method {
  int amount_of_arguments() const { return 2; }
  bool should_evaluate_arguments() const { return false; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    env.set(args.at(0).as_string(), evaluate(env, args.at(1), fcl));
    return data(data_type::none);
  }
};

class overload : public method {
  int amount_of_arguments() const { return 2; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (!utils::all_types_are(args, data_type::function)) {
      throw error(error_type::invalid_arguments, "Not A Function", fcl);
    }

    auto f = data(args.at(0)).as_function();
    f.merge_with_function(args.at(1).as_function());

    return data(data_type::function, f);
  }
};

class if_expression : public method {
  int amount_of_arguments() const { return 3; }
  bool should_evaluate_arguments() const { return false; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (evaluate(env, args.at(0), fcl).as_boolean())
      return evaluate(env, args.at(1), fcl);
    else
      return evaluate(env, args.at(2), fcl);
  }
};

class let_expression : public method {
  int amount_of_arguments() const { return 2; }
  bool should_evaluate_arguments() const { return false; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::map)
      throw error(error_type::invalid_arguments, "Not A HashMap", fcl);

    if (args.at(1).type() != data_type::process)
      throw error(error_type::invalid_arguments, "Not A Process", fcl);

    enviroment container_enviroment(env_type::let, &env);
    for (auto map_pair : args.at(0).as_map()) {
      if (map_pair.first.type() != data_type::symbol)
        throw xig::error(xig::error_type::invalid_arguments, "Not A Symbol",
                         fcl);

      container_enviroment.set(
          map_pair.first.as_symbol(),
          evaluate(container_enviroment, map_pair.second, fcl), true);
    }

    return evaluate(container_enviroment, args.at(1), fcl);
  }
};

class get_input : public method {
  int amount_of_arguments() const { return 0; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    std::string str;
    std::cin >> str;
    return data(data_type::string, str);
  }
};

class print_line : public method {
  int amount_of_arguments() const { return 1; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    std::cout << string_representation(args.at(0)) << std::endl;
    return data(data_type::none);
  }
};

class map : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    auto arguments = utils::parse_arguments(args, 2);

    if (arguments.size() > 2) {
      unsigned tuple_sizes = arguments.at(0).as_tuple().size();
      for (unsigned int i(1); i < arguments.size() - 1; i++) {
        if (arguments.at(i).as_tuple().size() != tuple_sizes)
          throw error(error_type::invalid_arguments,
                      "Tuple Lengths Are Different", fcl);
      }
    }

    std::vector<data> return_values;
    for (unsigned int i(0); i < arguments.at(1).as_tuple().size(); i++) {
      std::vector<data> temp_proc = { arguments.at(arguments.size() - 1) };
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

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::function)
      throw error(error_type::invalid_arguments, "Not A Function", fcl);

    if (args.at(1).type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fcl);

    std::vector<data> temp_proc = { args.at(0) };

    for (auto data : args.at(1).as_tuple())
      temp_proc.push_back(data);

    data temp_function(data_type::process, temp_proc);
    return evaluate(env, temp_function, fcl);
  }
};

class foldl : public method {
  int amount_of_arguments() const { return 3; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::function)
      throw error(error_type::invalid_arguments, "Not A Function", fcl);

    if (args.at(2).type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fcl);

    auto items = args.at(2).as_tuple();
    auto fn = args.at(0).as_function();

    auto ret = std::accumulate(items.begin(), items.end(), args.at(1),
                               [&](const data &a, const data &b) {
      std::vector<data> fn_args;
      fn_args.push_back(a);
      fn_args.push_back(b);
      return fn.call(fn_args, env, fcl);
    });

    return ret;
  }
};

class foldr : public method {
  int amount_of_arguments() const { return 3; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::function)
      throw error(error_type::invalid_arguments, "Not A Function", fcl);

    if (args.at(2).type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fcl);

    auto items = args.at(2).as_tuple();
    auto fn = args.at(0).as_function();

    auto ret = std::accumulate(items.rbegin(), items.rend(), args.at(1),
                               [&](const data &a, const data &b) {
      std::vector<data> fn_args;
      fn_args.push_back(b);
      fn_args.push_back(a);
      return fn.call(fn_args, env, fcl);
    });

    return ret;
  }
};

class filter : public method {
  int amount_of_arguments() const { return 2; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::function)
      throw error(error_type::invalid_arguments, "Not A Function", fcl);

    if (args.at(1).type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fcl);

    auto fn = args.at(0).as_function();
    auto original = args.at(1).as_tuple();
    std::vector<data> ret;
    std::copy_if(original.begin(), original.end(), std::back_inserter(ret),
                 [&](const data &i) {
      std::vector<data> a;
      a.push_back(i);
      return (make_boolean(true) == fn.call(a, env, fcl));
    });

    return make_tuple(ret);
  }
};

class partial : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::function)
      throw error(error_type::invalid_arguments, "Not A Function", fcl);

    auto arguments = utils::parse_arguments(args, 2);

    data captured_function = arguments.at(0);
    std::vector<data> captured_function_args(arguments.begin() + 1,
                                             arguments.end());

    struct fn : public method {
      data _captured_function;
      std::vector<data> _captured_function_args;

      fn(data func, std::vector<data> args)
          : _captured_function(func), _captured_function_args(args) {}

      int amount_of_arguments() const { return 0; }
      bool has_repeating_arguments() const { return true; }

      data run(std::vector<data> fn_args, enviroment &fn_env,
               std::vector<std::string> fn_fcl) {
        auto fn_arguments = utils::parse_arguments(fn_args, 0);
        std::vector<data> final_args = _captured_function_args;
        final_args.insert(final_args.end(), fn_arguments.begin(),
                          fn_arguments.end());
        return _captured_function.as_function().call(final_args, fn_env,
                                                     fn_fcl);
      }
    } return_method = { captured_function, captured_function_args };

    data return_function(data_type::function, function(return_method));
    return return_function;
  }
};

class macro : public method {
  int amount_of_arguments() const { return 2; }
  bool should_evaluate_arguments() const { return false; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fcl);

    if (args.at(1).type() != data_type::process)
      throw error(error_type::invalid_arguments, "Not A Process", fcl);

    for (const auto &i : args.at(0).as_tuple()) {
      if (i.type() != data_type::symbol)
        throw error(error_type::invalid_arguments, "Not A Symbol", fcl);
    }

    struct fn : public method {
      const data _captured_proc;
      const std::vector<data> _captured_proc_args;

      fn(data func, std::vector<data> args)
          : _captured_proc(func), _captured_proc_args(args) {}

      int amount_of_arguments() const { return _captured_proc_args.size(); }
      bool has_repeating_arguments() const { return false; }
      bool should_evaluate_arguments() const { return false; }

      std::vector<data> replace(std::vector<data> list,
                                const std::vector<data> &rp) {
        for (auto &i : list) {
          if (i.type() == data_type::tuple) {
            i = make_tuple(replace(i.as_tuple(), rp));
          } else if (i.type() == data_type::process) {
            i = make_process(replace(i.as_process(), rp));
          } else if (i.type() == data_type::symbol) {
            for (unsigned keyword_i(0); keyword_i < _captured_proc_args.size();
                 keyword_i++) {
              if (_captured_proc_args.at(keyword_i).as_symbol() ==
                  i.as_symbol()) {
                i = rp.at(keyword_i);
                break;
              }
            }
          }
        }
        return list;
      }

      data run(std::vector<data> fn_args, enviroment &fn_env,
               std::vector<std::string> fn_fcl) {
        auto new_proc = replace(_captured_proc.as_process(), fn_args);
        return evaluate(fn_env, make_process(new_proc), fn_fcl);
      }
    } return_method = { args.at(1), args.at(0).as_tuple() };

    data return_function(data_type::function, function(return_method));
    return return_function;
  }
};

class import : public method {
  int amount_of_arguments() const { return 1; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::string)
      throw error(error_type::invalid_arguments, "Not A Sring", fcl);

    auto file_name = args.at(0).as_string();
    evaluate(env, parser::from_file(file_name, env));

    return data(data_type::none);
  }
};

class import_as : public method {
  int amount_of_arguments() const { return 2; }
  bool should_evaluate_arguments() const { return false; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::symbol)
      throw error(error_type::invalid_arguments, "Not A Symbol", fcl);

    if (args.at(1).type() != data_type::string)
      throw error(error_type::invalid_arguments, "Not A Sring", fcl);

    auto file_name = args.at(1).as_string();
    auto import_name = args.at(0).as_symbol();

    env.set(import_name, make_container(enviroment(env_type::container, &env)));
    auto sub_env = env.find(import_name)->as_container();

    evaluate(*sub_env, parser::from_file(file_name, *sub_env));

    return data(data_type::none);
  }
};

class to_integer : public method {
  int amount_of_arguments() const { return 1; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    long long ret;

    if (args.at(0).type() == data_type::integer)
      ret = args.at(0).as_integer();
    else if (args.at(0).type() == data_type::decimal)
      ret = (long long)args.at(0).as_decimal();
    else
      throw error(error_type::invalid_arguments, "Not A Number", fcl);

    return data(data_type::integer, ret);
  }
};
}
}
