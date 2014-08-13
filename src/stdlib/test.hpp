#pragma once

#include <vector>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"

#include "stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class testeq : public method {
  int amount_of_arguments() const { return 3; }

  data run(call_info fci) {
    if (fci.args.at(0).type() != data_type::string)
      throw error(error_type::invalid_arguments, "Not A String", fci.debug);

    if (fci.args.at(1) == fci.args.at(2)) {
      std::cout << "Test Passed: " << fci.args.at(0).as_string() << std::endl;
    } else {
      std::cout << "****" << std::endl
                << "Test Failed: " << fci.args.at(0).as_string() << std::endl
                << "Args: " << string_representation(fci.args.at(1)) << ", "
                << string_representation(fci.args.at(2)) << std::endl << "****"
                << std::endl;
    }

    return make_none();
  }
};

class testne : public method {
  int amount_of_arguments() const { return 3; }

  data run(call_info fci) {
    if (fci.args.at(0).type() != data_type::string)
      throw error(error_type::invalid_arguments, "Not A String", fci.debug);

    if (fci.args.at(1) != fci.args.at(2)) {
      std::cout << "Test Passed: " << fci.args.at(0).as_string() << std::endl;
    } else {
      std::cout << "****" << std::endl
                << "Test Failed: " << fci.args.at(0).as_string() << std::endl
                << "Args: " << string_representation(fci.args.at(1)) << ", "
                << string_representation(fci.args.at(2)) << std::endl << "****"
                << std::endl;
    }

    return make_none();
  }
};

class testtr : public method {
  int amount_of_arguments() const { return 2; }

  data run(call_info fci) {
    if (fci.args.at(0).type() != data_type::string)
      throw error(error_type::invalid_arguments, "Not A String", fci.debug);

    if (fci.args.at(1).type() != data_type::boolean)
      throw error(error_type::invalid_arguments, "Not A Boolean", fci.debug);

    if (fci.args.at(1).as_boolean()) {
      std::cout << "Test Passed: " << fci.args.at(0).as_string() << std::endl;
    } else {
      std::cout << "****" << std::endl
                << "Test Failed: " << fci.args.at(0).as_string() << std::endl
                << "Args: " << string_representation(fci.args.at(1))
                << std::endl << "****" << std::endl;
    }

    return make_none();
  }
};
}
}
