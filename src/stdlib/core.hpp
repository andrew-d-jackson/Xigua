#pragma once

#include <vector>
#include <functional>
#include <memory>
#include <iterator>
#include <numeric>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"
#include "xigua/evaluate.hpp"
#include "xigua/parser.hpp"

#include "stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class define : public method {
  int amount_of_arguments() const { return 2; }
  bool should_evaluate_arguments() const { return false; }

  data_ptr run(call_info fci) {
    fci.env.set(fci.args.at(0)->as_symbol().as_std_string(),
                evaluate(fci.env, fci.args.at(1), fci.debug));

    return make_none();
  }
};

class overload : public method {
  int amount_of_arguments() const { return 2; }

  data_ptr run(call_info fci) {
    if (!utils::all_types_are(fci.args, data_type::function)) {
      throw error(error_type::invalid_arguments, "Not A Function", fci.debug);
    }

    auto f = fci.args.at(0)->as_function();
    f.merge_with_function(fci.args.at(1)->as_function());

    return make_function(f);
  }
};

class if_expression : public method {
  int amount_of_arguments() const { return 3; }
  bool should_evaluate_arguments() const { return false; }

  data_ptr run(call_info fci) {
    if (evaluate(fci.env, fci.args.at(0), fci.debug)->as_boolean())
      return evaluate(fci.env, fci.args.at(1), fci.debug);
    else
      return evaluate(fci.env, fci.args.at(2), fci.debug);
  }
};

class let_expression : public method {
  int amount_of_arguments() const { return 2; }
  bool should_evaluate_arguments() const { return false; }

  data_ptr run(call_info fci) {
    if (fci.args.at(0)->type() != data_type::map)
      throw error(error_type::invalid_arguments, "Not A HashMap", fci.debug);

    if (fci.args.at(1)->type() != data_type::process)
      throw error(error_type::invalid_arguments, "Not A Process", fci.debug);

    enviroment container_enviroment(env_type::let, &fci.env);
    for (auto map_pair : fci.args.at(0)->as_map()) {
      if (map_pair.first->type() != data_type::symbol)
        throw xig::error(xig::error_type::invalid_arguments, "Not A Symbol",
                         fci.debug);

      container_enviroment.set(
          map_pair.first->as_symbol(),
          evaluate(container_enviroment, map_pair.second, fci.debug), true);
    }

    return evaluate(container_enviroment, fci.args.at(1), fci.debug);
  }
};

class get_input : public method {
  int amount_of_arguments() const { return 0; }

  data_ptr run(call_info fci) {
    std::string str;
    std::cin >> str;
    return make_string(str);
  }
};

class print_line : public method {
  int amount_of_arguments() const { return 1; }

  data_ptr run(call_info fci) {
    std::cout << string_representation(fci.args.at(0)) << std::endl;
    return make_none();
  }
};

class map : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data_ptr run(call_info fci) {
    auto arguments = utils::parse_arguments(fci.args, 2);

    if (arguments.size() > 2) {
      unsigned tuple_sizes = arguments.at(0)->as_tuple().size();
      for (unsigned i(1); i < arguments.size() - 1; i++) {
        if (arguments.at(i)->as_tuple().size() != tuple_sizes)
          throw error(error_type::invalid_arguments,
                      "Tuple Lengths Are Different", fci.debug);
      }
    }

    std::vector<data_ptr> return_values;
    for (unsigned int i(0); i < arguments.at(1)->as_tuple().size(); i++) {
      std::vector<data_ptr> temp_proc = {arguments.at(arguments.size() - 1)};
      for (unsigned int j(0); j < arguments.size() - 1; j++)
        temp_proc.push_back(arguments.at(j)->as_tuple().at(i));

      auto temp_function = make_process(temp_proc);
      return_values.push_back(evaluate(fci.env, temp_function, fci.debug));
    }

    return make_tuple(return_values);
  }
};

class apply : public method {
  int amount_of_arguments() const { return 2; }

  data_ptr run(call_info fci) {
    if (fci.args.at(0)->type() != data_type::function)
      throw error(error_type::invalid_arguments, "Not A Function", fci.debug);

    if (fci.args.at(1)->type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

    std::vector<data_ptr> temp_proc = {fci.args.at(0)};

    for (auto d : fci.args.at(1)->as_tuple())
      temp_proc.push_back(d);

    auto temp_function = make_process(temp_proc);
    return evaluate(fci.env, temp_function, fci.debug);
  }
};

class foldl : public method {
  int amount_of_arguments() const { return 3; }

  data_ptr run(call_info fci) {
    if (fci.args.at(0)->type() != data_type::function)
      throw error(error_type::invalid_arguments, "Not A Function", fci.debug);

    if (fci.args.at(2)->type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

    auto items = fci.args.at(2)->as_tuple();
    auto fn = fci.args.at(0)->as_function();

    auto ret = std::accumulate(items.begin(), items.end(), fci.args.at(1),
                               [&](const data_ptr &a, const data_ptr &b) {
      std::vector<data_ptr> fn_args;
      fn_args.push_back(a);
      fn_args.push_back(b);
      return fn.call({fn_args, fci.env, fci.debug});
    });

    return ret;
  }
};

class foldr : public method {
  int amount_of_arguments() const { return 3; }

  data_ptr run(call_info fci) {
    if (fci.args.at(0)->type() != data_type::function)
      throw error(error_type::invalid_arguments, "Not A Function", fci.debug);

    if (fci.args.at(2)->type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

    auto items = fci.args.at(2)->as_tuple();
    auto fn = fci.args.at(0)->as_function();

    auto ret = std::accumulate(items.begin(), items.end(), fci.args.at(1),
                               [&](const data_ptr &a, const data_ptr &b) {
      std::vector<data_ptr> fn_args;
      fn_args.push_back(b);
      fn_args.push_back(a);
      return fn.call({fn_args, fci.env, fci.debug});
    });

    return ret;
  }
};

class filter : public method {
  int amount_of_arguments() const { return 2; }

  data_ptr run(call_info fci) {
    if (fci.args.at(0)->type() != data_type::function)
      throw error(error_type::invalid_arguments, "Not A Function", fci.debug);

    if (fci.args.at(1)->type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

    auto fn = fci.args.at(0)->as_function();
    auto original = fci.args.at(1)->as_tuple();
    std::vector<data_ptr> ret;
    std::copy_if(original.begin(), original.end(), std::back_inserter(ret),
                 [&](const data_ptr &i) {
      std::vector<data_ptr> a;
      a.push_back(i);
      return (make_boolean(true) == fn.call({a, fci.env, fci.debug}));
    });

    return make_tuple(ret);
  }
};

class partial : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data_ptr run(call_info fci) {
    if (fci.args.at(0)->type() != data_type::function)
      throw error(error_type::invalid_arguments, "Not A Function", fci.debug);

    auto arguments = utils::parse_arguments(fci.args, 2);

    data_ptr captured_function = arguments.at(0);
    std::vector<data_ptr> captured_function_args(arguments.begin() + 1,
                                                 arguments.end());

    struct fn : public method {
      data_ptr _captured_function;
      std::vector<data_ptr> _captured_function_args;

      fn(data_ptr func, std::vector<data_ptr> args)
          : _captured_function(func), _captured_function_args(args) {}

      int amount_of_arguments() const { return 0; }
      bool has_repeating_arguments() const { return true; }

      data_ptr run(call_info fn_fci) {
        auto fn_arguments = utils::parse_arguments(fn_fci.args, 0);
        std::vector<data_ptr> final_args = _captured_function_args;
        final_args.insert(final_args.end(), fn_arguments.begin(),
                          fn_arguments.end());
        return _captured_function->as_function().call(
            {final_args, fn_fci.env, fn_fci.debug});
      }
    } return_method = {captured_function, captured_function_args};

    auto return_function = make_function(return_method);
    return return_function;
  }
};

class macro : public method {
  int amount_of_arguments() const { return 2; }
  bool should_evaluate_arguments() const { return false; }

  data_ptr run(call_info fci) {
    if (fci.args.at(0)->type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

    if (fci.args.at(1)->type() != data_type::process)
      throw error(error_type::invalid_arguments, "Not A Process", fci.debug);

    for (const auto &i : fci.args.at(0)->as_tuple()) {
      if (i->type() != data_type::symbol)
        throw error(error_type::invalid_arguments, "Not A Symbol", fci.debug);
    }

    struct fn : public method {
      const data_ptr _captured_proc;
      const std::vector<data_ptr> _captured_proc_args;

      fn(data_ptr func, std::vector<data_ptr> args)
          : _captured_proc(func), _captured_proc_args(args) {}

      int amount_of_arguments() const { return _captured_proc_args.size(); }
      bool has_repeating_arguments() const { return false; }
      bool should_evaluate_arguments() const { return false; }

      std::vector<data_ptr> replace(std::vector<data_ptr> list,
                                    const std::vector<data_ptr> &rp) {
        for (auto &i : list) {
          if (i->type() == data_type::tuple) {
            i = make_tuple(replace(i->as_tuple().as_std_vector(), rp));
          } else if (i->type() == data_type::process) {
            i = make_process(replace(i->as_process().as_std_vector(), rp));
          } else if (i->type() == data_type::symbol) {
            for (unsigned keyword_i(0); keyword_i < _captured_proc_args.size();
                 keyword_i++) {
              if (_captured_proc_args.at(keyword_i)->as_symbol() ==
                  i->as_symbol()) {
                i = rp.at(keyword_i);
                break;
              }
            }
          }
        }
        return list;
      }

      data_ptr run(call_info fn_fci) {
        auto new_proc =
            replace(_captured_proc->as_process().as_std_vector(), fn_fci.args);
        return evaluate(fn_fci.env, make_process(new_proc), fn_fci.debug);
      }
    } return_method = {fci.args.at(1), fci.args.at(0)->as_tuple()};

    return make_function(return_method);
  }
};

class import : public method {
  int amount_of_arguments() const { return 1; }

  data_ptr run(call_info fci) {
    if (fci.args.at(0)->type() != data_type::string)
      throw error(error_type::invalid_arguments, "Not A Sring", fci.debug);

    auto file_name = fci.args.at(0)->as_string().as_std_string();
    evaluate(fci.env, parser::from_file(file_name, fci.env));

    return make_none();
  }
};

class import_as : public method {
  int amount_of_arguments() const { return 2; }
  bool should_evaluate_arguments() const { return false; }

  data_ptr run(call_info fci) {
    if (fci.args.at(0)->type() != data_type::symbol)
      throw error(error_type::invalid_arguments, "Not A Symbol", fci.debug);

    if (fci.args.at(1)->type() != data_type::string)
      throw error(error_type::invalid_arguments, "Not A Sring", fci.debug);

    auto file_name = fci.args.at(1)->as_string().as_std_string();
    auto import_name = fci.args.at(0)->as_symbol().as_std_string();

    fci.env.set(import_name,
                std::make_shared<enviroment>(env_type::container, &fci.env));
    auto sub_env = fci.env.find(import_name)->as_enviroment();

    evaluate(sub_env, parser::from_file(file_name, sub_env));

    return make_none();
  }
};

class to_integer : public method {
  int amount_of_arguments() const { return 1; }

  data_ptr run(call_info fci) {
    long long ret;

    if (fci.args.at(0)->type() == data_type::integer)
      ret = fci.args.at(0)->as_integer().as_int();
    else if (fci.args.at(0)->type() == data_type::decimal)
      ret = (long long)fci.args.at(0)->as_decimal().as_double();
    else
      throw error(error_type::invalid_arguments, "Not A Number", fci.debug);

    return make_integer(ret);
  }
};
}
}
