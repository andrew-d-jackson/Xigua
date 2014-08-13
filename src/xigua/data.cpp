#include "xigua/data.hpp"

namespace xig {
std::string string_representation(const data_ptr &d) {
  const auto &in_data = *d;
  std::string return_value = "";
  if (in_data.type() == data_type::string) {
    return_value += in_data.as_string().as_std_string();
  } else if (in_data.type() == data_type::keyword) {
    return_value += ":" + in_data.as_string().as_std_string();
  } else if (in_data.type() == data_type::symbol) {
    return_value += in_data.as_symbol().as_std_string();
  } else if (in_data.type() == data_type::boolean) {
    if (in_data.as_boolean()) {
      return_value += "true";
    } else {
      return_value += "false";
    }
  } else if (in_data.type() == data_type::decimal) {
    std::stringstream ss;
    ss << std::fixed;
    ss << in_data.as_decimal().as_double();
    std::string str = ss.str();
    int s;
    for (s = str.length() - 1; s > 0; s--) {
      if (str[s] == '0')
        str.erase(s, 1);
      else
        break;
    }
    if (str[s] == '.')
      str.erase(s, 1);
    return_value += str;
  } else if (in_data.type() == data_type::integer) {
    return_value += std::to_string(in_data.as_integer().as_int());
  } else if (in_data.type() == data_type::tuple) {
    return_value += "{ ";
    for (auto element : in_data.as_tuple().as_std_vector()) {
      return_value += string_representation(element);
      return_value += " ";
    }
    return_value += "}";
  } else if (in_data.type() == data_type::map) {
    return_value += "#{ ";
    for (auto &element : in_data.as_map().as_std_map()) {
      return_value += string_representation(element.first);
      return_value += " => ";
      return_value += string_representation(element.second);
      return_value += ", ";
    }
    return_value += "}";
  } else if (in_data.type() == data_type::process) {
    return_value += "[ ";
    for (auto element : in_data.as_process().as_std_vector()) {
      return_value += string_representation(element);
      return_value += " ";
    }
    return_value += "]";
  }
  return return_value;
}
}
