#pragma once

#include <vector>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"

#include "xigua/stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class type_query_base : public method {
  int amount_of_arguments() const { return 1; }

  virtual data_type expected_type() const = 0;

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    auto argument_type = args.at(0).type();

    bool ret = false;
    if (argument_type == expected_type())
      ret = true;

    return data(data_type::boolean, ret);
  }
};

class is_string : public type_query_base {
  data_type expected_type() const { return data_type::string; }
};
class is_number : public type_query_base {
  data_type expected_type() const { return data_type::number; }
};
class is_boolean : public type_query_base {
  data_type expected_type() const { return data_type::boolean; }
};
class is_tuple : public type_query_base {
  data_type expected_type() const { return data_type::tuple; }
};
class is_map : public type_query_base {
  data_type expected_type() const { return data_type::map; }
};
class is_none : public type_query_base {
  data_type expected_type() const { return data_type::none; }
};
class is_keyword : public type_query_base {
  data_type expected_type() const { return data_type::keyword; }
};
class is_function : public type_query_base {
  data_type expected_type() const { return data_type::function; }
};
}
}
