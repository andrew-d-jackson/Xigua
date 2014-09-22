#pragma once

#include <vector>
#include <algorithm>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"

#include "stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class at : public method {
  int amount_of_arguments() const { return 2; }

  data_ptr run(call_info fci) {
    if (fci.args.at(1)->type() == data_type::tuple) {
      if (fci.args.at(0)->type() != data_type::integer)
        throw error(error_type::invalid_arguments, "Not An Integer", fci.debug);

      if (fci.args.at(0)->as_integer().as_int() < 0 ||
          fci.args.at(0)->as_integer().as_int() >
              fci.args.at(1)->as_tuple().size() - 1)
        throw error(error_type::invalid_arguments, "Not In Range Of Tuple",
                    fci.debug);

      return fci.args.at(1)->as_tuple().at(
          (unsigned int)fci.args.at(0)->as_integer().as_int());

    } else if (fci.args.at(1)->type() == data_type::map) {
        auto map = fci.args.at(1)->as_map().as_std_map();
        auto location = std::find_if(map.begin(), map.end(),
                [&](const std::pair<data_ptr, data_ptr> &i) {
                    return *(i.first) == *fci.args.at(0);
                });
        if (location != map.end()) {
            return location->second;
        } else {
            throw error(error_type::invalid_arguments, "Not In HashMap", fci.debug);
        }
    } else if (fci.args.at(1)->type() == data_type::record_object) {
        if (fci.args.at(0)->type() != data_type::keyword)
            throw error(error_type::invalid_arguments, "Not A Keyword", fci.debug);

        auto map = fci.args.at(1)->as_record_object();
        auto location = std::find_if(map.begin(), map.end(),
                [&](const record_variable_object &i) {
                    return i.definition->name == fci.args.at(0)->as_keyword().as_std_string();
                });
        if (location != map.end()) {
            return location->value;
        } else {
            throw error(error_type::invalid_arguments, "Not In Container", fci.debug);
        }
    } else {
      throw error(error_type::invalid_arguments, "Not A HashMap Or A Tuple Or A Record",
                  fci.debug);
    }
    return make_none();
  }
};

class size : public method {
  int amount_of_arguments() const { return 1; }

  data_ptr run(call_info fci) {
    if (fci.args.at(0)->type() == data_type::tuple)
      return make_integer((long long)fci.args.at(0)->as_tuple().size());

      if (fci.args.at(0)->type() == data_type::map)
          return make_integer((long long)fci.args.at(0)->as_map().size());

      if (fci.args.at(0)->type() == data_type::record_definition)
          return make_integer((long long)fci.args.at(0)->as_record_definition().size());

      if (fci.args.at(0)->type() == data_type::record_object)
          return make_integer((long long)fci.args.at(0)->as_record_object().size());

    throw error(error_type::invalid_arguments, "Not A HashMap Or A Tuple",
                fci.debug);

    return make_none();
  }
};

class insert : public method {
  int amount_of_arguments() const { return 2; }
  bool has_repeating_arguments() const { return true; }

  data_ptr run(call_info fci) {

    auto arguments = utils::parse_arguments(fci.args, 2);

    if (arguments.at(0)->type() == data_type::tuple) {
      auto new_tuple = arguments.at(0)->as_tuple().as_std_vector();
      new_tuple.push_back(arguments.at(1));
      return make_tuple(new_tuple);
    }

          if (arguments.at(0)->type() == data_type::map) {
              auto new_map = arguments.at(0)->as_map().as_std_map();
              new_map[arguments.at(1)] = arguments.at(2);
              return make_map(new_map);
          }

          if (arguments.at(0)->type() == data_type::record_definition) {
              auto new_vec = arguments.at(0)->as_record_definition().as_std_vector();
              new_vec.push_back({arguments.at(1)->as_keyword().as_std_string(), {}});
              return make_record_definition(new_vec);
          }

    throw error(error_type::invalid_arguments, "Not A HashMap Or A Tuple",
                fci.debug);
    return make_none();
  }
};
}
}
