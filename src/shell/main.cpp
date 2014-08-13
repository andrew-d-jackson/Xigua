#include <iostream>
#include <string>

#include "xigua/xigua.hpp"
#include "xigua/stdlib.hpp"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    xig::enviroment enviroment = xig::stdlib::get_global_enviroment();
    try {
      xig::evaluate(enviroment, xig::parser::from_file(argv[1], enviroment));
    } catch (xig::error e) {
      e.print_default_message();
    }
  } else {
    std::cout << "Xigua REPL" << std::endl;
    xig::enviroment enviroment = xig::stdlib::get_global_enviroment();
    std::string input;
    while (std::getline(std::cin, input)) {
      if (input == "exit")
        break;
      try {
        std::cout << xig::string_representation(xig::evaluate(
                         enviroment, xig::parser::from_string(input)))
                  << std::endl;
      } catch (xig::error e) {
        e.print_default_message();
      }
    }
  }
}
