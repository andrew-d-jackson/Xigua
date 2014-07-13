#pragma once

#include <vector>
#include <algorithm>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"

#include "xigua/stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class join : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data run(call_info fci) {
    auto arguments = utils::parse_arguments(fci.args, 2);
    std::vector<data> return_value;
    for (auto argument : arguments) {
      if (argument.type() == data_type::tuple) {
        for (auto element : argument.as_tuple())
          return_value.push_back(element);
      } else {
        return_value.push_back(argument);
      }
    }
    return data(data_type::tuple, return_value);
  }
};

class unique : public method {
  int amount_of_arguments() const { return 1; }

  data run(call_info fci) {
    if (fci.args.at(0).type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

    auto initial_tuple = fci.args.at(0).as_tuple();
    std::sort(initial_tuple.begin(), initial_tuple.end());
    auto unique_iterator =
        std::unique(initial_tuple.begin(), initial_tuple.end());
    std::vector<data> return_value(initial_tuple.begin(), unique_iterator);

    return data(data_type::tuple, return_value);
  }
};

class first : public method {
  int amount_of_arguments() const { return 1; }

  data run(call_info fci) {
    if (fci.args.at(0).type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

    if (fci.args.at(0).as_tuple().size() < 1)
      throw error(error_type::invalid_arguments, "Not In Range", fci.debug);

    return fci.args.at(0).as_tuple().at(0);
  }
};

class last : public method {
  int amount_of_arguments() const { return 1; }

  data run(call_info fci) {
    if (fci.args.at(0).type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

    if (fci.args.at(0).as_tuple().size() < 1)
      throw error(error_type::invalid_arguments, "Not In Range", fci.debug);

    return fci.args.at(0).as_tuple().at(fci.args.at(0).as_tuple().size() - 1);
  }
};

class tail : public method {
  int amount_of_arguments() const { return 1; }

  data run(call_info fci) {
    if (fci.args.at(0).type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

    if (fci.args.at(0).as_tuple().size() < 1)
      throw error(error_type::invalid_arguments, "Not In Range", fci.debug);

    auto t = fci.args.at(0).as_tuple();
    auto s = std::vector<data>(t.begin() + 1, t.end());

    return make_tuple(s);
  }
};

class init : public method {
  int amount_of_arguments() const { return 1; }

  data run(call_info fci) {
    if (fci.args.at(0).type() != data_type::tuple)
      throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

    if (fci.args.at(0).as_tuple().size() < 1)
      throw error(error_type::invalid_arguments, "Not In Range", fci.debug);

    auto t = fci.args.at(0).as_tuple();
    auto s = std::vector<data>(t.begin(), t.end() - 1);

    return make_tuple(s);
  }
};

class range : public method {
  int amount_of_arguments() const { return 3; }

  data run(call_info fci) {
    if (!utils::all_types_are(fci.args, data_type::integer))
      throw error(error_type::invalid_arguments, "Not A Integer", fci.debug);

    long long start = fci.args.at(0).as_integer();
    long long end = fci.args.at(1).as_integer();
    long long step = fci.args.at(2).as_integer();

    if (start > end && step >= 0)
      throw error(error_type::invalid_arguments, "Range Invalid", fci.debug);
    else if (start < end && step <= 0)
      throw error(error_type::invalid_arguments, "Range Invalid", fci.debug);
    else if (step == 0 || start == end)
      throw error(error_type::invalid_arguments, "Range Invalid", fci.debug);

    std::vector<data> return_value;

    if (start > end) {
      while (start > end) {
        return_value.push_back(data(start));
        start += step;
      }
    } else if (start < end) {
      while (start < end) {
        return_value.push_back(data(start));
        start += step;
      }
    }

    return data(data_type::tuple, return_value);
  }
};
}
}
