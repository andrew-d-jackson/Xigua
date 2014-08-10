#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "xigua/data.hpp"
#include "xigua/error.hpp"
#include "xigua/enviroment.hpp"

namespace xig {

class parser {
public:
  static data_ptr from_file(std::string file_location, enviroment &env);
  static data_ptr from_string(const std::string source_code);

private:
  static std::string read_file(const std::string file_location);

  static std::vector<std::string>
  source_to_string_list(const std::string source_code);
  static void validate_string_list(const std::vector<std::string> string_list);

  static data_ptr
  string_list_to_data_type(const std::vector<std::string> string_list);
  static data_ptr
  string_list_to_data_type(const std::vector<std::string> string_list,
                           const data_type list_type);
  static data_ptr string_to_data_type(const std::string input_string);
  static bool is_integer(std::string string);
  static bool is_decimal(std::string string);
};
}
