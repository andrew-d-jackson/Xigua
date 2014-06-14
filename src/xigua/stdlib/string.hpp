#pragma once

#include <vector>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"

#include "xigua/stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class concatinate : public method {
  int amount_of_arguments() const { return 1; }
  bool has_repeating_arguments() const { return true; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    auto arguments = utils::parse_arguments(args, 1);

    std::string return_string = "";
    for (auto argument : arguments) {
      return_string += string_representation(argument);
    }

    return data(data_type::string, return_string);
  }
};

class substring : public method {
  int amount_of_arguments() const { return 3; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::string)
      throw error(error_type::invalid_arguments, "Not A String", fcl);

    if (args.at(1).type() != data_type::integer ||
        args.at(2).type() != data_type::integer)
      throw error(error_type::invalid_arguments, "Not A Integer", fcl);

    std::string start_string = args.at(0).as_string();
    int start_pos = (int)args.at(1).as_integer();
    int length = (int)args.at(2).as_integer() - start_pos;

    std::string return_string = start_string.substr(start_pos, length + 1);
    return data(data_type::string, return_string);
  }
};
}
}
