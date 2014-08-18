#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace xig {

//! Enum for the different types of errors
enum class error_type {
  internal_error,
  unmatching_brackets,
  invalid_arguments,
  parsing_error,
};

struct debug_info {
	std::vector<std::string> function_call_list;
	debug_info() { function_call_list = {}; }
	debug_info(std::vector<std::string> fcl) { function_call_list = fcl; }
};

//! Error class that will be thrown as an exception if something goes wrong with
//! Xigua
class error {
private:
  error_type my_error_type;
  std::string descripton;
  std::vector<std::string> function_call_list;

public:
  //! Construct an error with a type, description to be printed to the end user,
  // and the function call list
  error(error_type e_type, std::string descripton, debug_info debug);
  error(error_type e_type, std::string descripton);

  //! Get the errors type
  error_type get_error_type() const;
  //! Get the errors description
  std::string get_description() const;
  //! Get the list of Xigua functions that were called upto throwing the error
  std::vector<std::string> get_function_call_list() const;

  //! Print a default error message to the end user
  void print_default_message() const;
};
}
