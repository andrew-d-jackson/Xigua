#pragma once

#include <vector>
#include <cmath>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"

#include "stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class comparator : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  virtual bool all_types_must_be_numbers() const { return true; }

  virtual bool compare_integer(long long a, long long b) const = 0;
  virtual bool compare_decimal(long double a, long double b) const = 0;

  data_ptr run(call_info fci) {
    auto arguments = utils::parse_arguments(fci.args, 2);
    for (const auto &arg : arguments)
      if (!(arg->type() == data_type::decimal ||
            arg->type() == data_type::integer))
        throw error(error_type::invalid_arguments, "Not A Number", fci.debug);

    for (auto it = arguments.begin(); it < arguments.end() - 1; it++) {
      if ((*it)->type() == data_type::decimal ||
          (*(it + 1))->type() == data_type::decimal) {
        auto a = (*it)->type() == data_type::decimal
                     ? (*it)->as_decimal().as_double()
                     : (long double)(*it)->as_integer().as_int();
        auto b = (*(it + 1))->type() == data_type::decimal
                     ? (*(it + 1))->as_decimal().as_double()
                     : (long double)(*(it + 1))->as_integer().as_int();
        if (!compare_decimal(a, b))
          return make_boolean(false);
      } else {
        if (!compare_integer((*it)->as_integer().as_int(),
                             (*(it + 1))->as_integer().as_int()))
          return make_boolean(false);
      }
    }
    return make_boolean(true);
  }
};

class less_than : public comparator {
  bool compare_decimal(long double a, long double b) const { return (a < b); }
  bool compare_integer(long long a, long long b) const { return (a < b); }
};

class greater_than : public comparator {
  bool compare_decimal(long double a, long double b) const { return (a > b); }
  bool compare_integer(long long a, long long b) const { return (a > b); }
};

class less_than_or_equal : public comparator {
  bool compare_decimal(long double a, long double b) const { return (a <= b); }
  bool compare_integer(long long a, long long b) const { return (a <= b); }
};

class greater_than_or_equal : public comparator {
  bool compare_decimal(long double a, long double b) const { return (a >= b); }
  bool compare_integer(long long a, long long b) const { return (a >= b); }
};

class equal_to : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data_ptr run(call_info fci) {
    auto arguments = utils::parse_arguments(fci.args, 2);
    for (auto it = arguments.begin(); it < arguments.end() - 1; it++) {
      if (*(*it) != *(*(it + 1)))
        return make_boolean(false);
    }
    return make_boolean(true);
  }
};

class math_operation : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }
  virtual bool always_decimal() const { return false; }

  virtual long long operate_integer(long long a, long long b) const {
    return 0;
  };
  virtual long double operate_decimal(long double a, long double b) const = 0;

  data_ptr run(call_info fci) {

    auto arguments = utils::parse_arguments(fci.args, 2);
    for (const auto &arg : arguments)
      if (!(arg->type() == data_type::decimal ||
            arg->type() == data_type::integer))
        throw error(error_type::invalid_arguments, "Not A Number", fci.debug);

    if (utils::all_types_are(arguments, data_type::integer) &&
        !always_decimal()) {
      long long return_value = arguments.at(0)->as_integer().as_int();
      for (auto it = arguments.begin() + 1; it < arguments.end(); it++) {
        return_value =
            operate_integer(return_value, (*it)->as_integer().as_int());
      }
      return make_integer(return_value);
    }

    long double return_value =
        arguments.at(0)->type() == data_type::decimal
            ? arguments.at(0)->as_decimal().as_double()
            : (long double)arguments.at(0)->as_integer().as_int();

    for (auto it = arguments.begin() + 1; it < arguments.end(); it++) {
      long double next_num = (*it)->type() == data_type::decimal
                                 ? (*it)->as_decimal().as_double()
                                 : (long double)(*it)->as_integer().as_int();

      return_value = operate_decimal(return_value, next_num);
    }
    return make_decimal(return_value);
  }
};

class add : public math_operation {
  long double operate_decimal(long double a, long double b) const {
    return a + b;
  }
  long long operate_integer(long long a, long long b) const { return a + b; }
};

class minus : public math_operation {
  long double operate_decimal(long double a, long double b) const {
    return a - b;
  }
  long long operate_integer(long long a, long long b) const { return a - b; }
};

class multiply : public math_operation {
  long double operate_decimal(long double a, long double b) const {
    return a * b;
  }
  long long operate_integer(long long a, long long b) const { return a * b; }
};

class divide : public math_operation {
  bool always_decimal() const { return true; }
  long double operate_decimal(long double a, long double b) const {
    return a / b;
  }
};

class modulo : public method {
  int amount_of_arguments() const { return 2; }

  data_ptr run(call_info fci) {
    for (const auto &arg : fci.args)
      if (!(arg->type() == data_type::decimal ||
            arg->type() == data_type::integer))
        throw error(error_type::invalid_arguments, "Not A Number", fci.debug);

    if (fci.args.at(0)->type() == data_type::decimal ||
        fci.args.at(1)->type() == data_type::decimal) {
      auto a = fci.args.at(0)->type() == data_type::decimal
                   ? fci.args.at(0)->as_decimal().as_double()
                   : (long double)fci.args.at(0)->as_integer().as_int();
      auto b = fci.args.at(1)->type() == data_type::decimal
                   ? fci.args.at(1)->as_decimal().as_double()
                   : (long double)fci.args.at(1)->as_integer().as_int();
      return make_decimal(std::fmod(a, b));
    } else {
      return make_integer(fci.args.at(0)->as_integer().as_int() %
                          fci.args.at(1)->as_integer().as_int());
    }
  }
};
}
}
