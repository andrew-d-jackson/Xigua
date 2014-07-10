#pragma once

#include <vector>
#include <algorithm>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"

#include "xigua/stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class boolean_not : public method {
  int amount_of_arguments() const { return 1; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::boolean)
      throw error(error_type::invalid_arguments, "Not A Boolean", fcl);

    return data(!(args.at(0).as_boolean()));
  }
};

class boolean_and : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    auto inputs = utils::parse_arguments(args, 2);
    if (!utils::all_types_are(inputs, data_type::boolean))
      throw error(error_type::invalid_arguments, "Not A Boolean", fcl);

    return make_boolean(std::find(inputs.begin(), inputs.end(),
                                  make_boolean(false)) == inputs.end());
  }
};

class boolean_or : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    auto inputs = utils::parse_arguments(args, 2);
    if (!utils::all_types_are(inputs, data_type::boolean))
      throw error(error_type::invalid_arguments, "Not A Boolean", fcl);

    return make_boolean(std::find(inputs.begin(), inputs.end(),
                                  make_boolean(true)) != inputs.end());
  }
};
}
}
