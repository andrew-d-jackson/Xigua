#include "xigua/error.hpp"
#include "xigua/data.hpp"
#include "xigua/function.hpp"

namespace xig {

error::error(error_type e_type, std::string descripton, debug_info debug) {
  this->my_error_type = e_type;
  this->descripton = descripton;
  this->function_call_list = debug.function_call_list;
}

error::error(error_type e_type, std::string descripton) {
  this->my_error_type = e_type;
  this->descripton = descripton;
  this->function_call_list = {};
}

error_type error::get_error_type() const {
  return my_error_type;
};

std::string error::get_description() const {
  return descripton;
};

std::vector<std::string> error::get_function_call_list() const {
  return function_call_list;
};

void error::print_default_message() const {
  std::cout << "Error: " << (int)my_error_type << std::endl;

  std::cout << "Description: " << descripton << std::endl;

  std::cout << "Function Call List: root";
  for (auto f_name : function_call_list) {
    std::cout << " -> " << f_name;
  }
  std::cout << std::endl;
};
}
