#pragma once

#include <vector>
#include <algorithm>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"

#include "stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class boolean_not : public method {
  int amount_of_arguments() const { return 1; }

  data run(call_info fci) {
    if (fci.args.at(0).type() != data_type::boolean)
      throw error(error_type::invalid_arguments, "Not A Boolean", fci.debug);

    return data(!fci.args.at(0));
  }
};

class boolean_and : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data run(call_info fci) {
    auto inputs = utils::parse_arguments(fci.args, 2);
    if (!utils::all_types_are(inputs, data_type::boolean))
      throw error(error_type::invalid_arguments, "Not A Boolean", fci.debug);

    return make_boolean(std::find(inputs.begin(), inputs.end(),
                                  make_boolean(false)) == inputs.end());
  }
};

class boolean_or : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data run(call_info fci) {
    auto inputs = utils::parse_arguments(fci.args, 2);
    if (!utils::all_types_are(inputs, data_type::boolean))
      throw error(error_type::invalid_arguments, "Not A Boolean", fci.debug);

    return make_boolean(std::find(inputs.begin(), inputs.end(),
                                  make_boolean(true)) != inputs.end());
  }
};
}
}
