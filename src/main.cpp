#include <iostream>
#include <string>

#include "enviroment.hpp"
#include "stdlib.hpp"
#include "parser.hpp"
#include "error.hpp"
#include "evaluate.hpp"

#ifdef TEST
#include "gtest/gtest.h"
#endif

int main(int argc, char *argv [])
{ 
#ifdef TEST

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

#else

	if (argc > 1) {
		xig::enviroment enviroment = xig::get_global_enviroment();
		try {
			xig::evaluate(enviroment, xig::parser::from_file(argv[1]));
		} catch (xig::error e) {
			e.print_default_message();
		}
	} else {
		std::cout << "Xigua REPL" << std::endl;
		xig::enviroment enviroment = xig::get_global_enviroment();
		std::string input;
		while (std::getline(std::cin,input)) {
			if (input == "exit") break;
			try {
				std::cout << xig::string_representation(xig::evaluate(enviroment, xig::parser::from_string(input))) << std::endl;
			} catch (xig::error e) {
				e.print_default_message();
			}
		}
		

	}
	

#endif
}