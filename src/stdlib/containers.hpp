#pragma once

#include <vector>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"

#include "stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class at : public method {
  int amount_of_arguments() const { return 2; }

  data run(call_info fci) {
    if (fci.args.at(1).type() == data_type::tuple) {
      if (fci.args.at(0).type() != data_type::integer)
        throw error(error_type::invalid_arguments, "Not An Integer", fci.debug);

      if (fci.args.at(0).as_integer() < 0 ||
          fci.args.at(0).as_integer() > fci.args.at(1).as_tuple().size() - 1)
        throw error(error_type::invalid_arguments, "Not In Range Of Tuple",
                    fci.debug);
      return fci.args.at(1).as_tuple().at(
          (unsigned int)fci.args.at(0).as_integer());
    } else if (fci.args.at(1).type() == data_type::map) {
      auto map = fci.args.at(1).as_map();
      auto location = map.find(fci.args.at(0));
      if (location != map.end()) {
        return location->second;
      } else {
        throw error(error_type::invalid_arguments, "Not In HashMap", fci.debug);
      }
    } else {
      throw error(error_type::invalid_arguments, "Not A HashMap Or A Tuple",
                  fci.debug);
    }
    return make_none();
  }
};

class size : public method {
  int amount_of_arguments() const { return 1; }

  data run(call_info fci) {
    if (fci.args.at(0).type() == data_type::tuple)
      return data((long long)fci.args.at(0).as_tuple().size());

    if (fci.args.at(0).type() == data_type::map)
      return data((long long)fci.args.at(0).as_map().size());

    throw error(error_type::invalid_arguments, "Not A HashMap Or A Tuple",
                fci.debug);
    return make_none();
  }
};

class insert : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data run(call_info fci) {

    auto arguments = utils::parse_arguments(fci.args, 2);

    if (arguments.at(0).type() == data_type::tuple) {
      auto new_tuple = arguments.at(0).as_tuple();
      new_tuple.push_back(arguments.at(1));
      return make_tuple(new_tuple);
    }

    if (arguments.at(0).type() == data_type::map) {
      auto new_map = arguments.at(0).as_map();
      new_map[arguments.at(1)] = arguments.at(2);
      return make_map(new_map);
    }

    throw error(error_type::invalid_arguments, "Not A HashMap Or A Tuple",
                fci.debug);
    return make_none();
  }
};
}
}
