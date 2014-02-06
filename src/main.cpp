#include <iostream>

#include "enviroment.hpp"
#include "stdlib.hpp"
#include "parser.hpp"
#include "error.hpp"
#include "evaluate.hpp"


#ifdef TEST

#include "gtest/gtest.h"

	int main(int argc, char *argv [])
	{ 
		::testing::InitGoogleTest(&argc, argv);
  		return RUN_ALL_TESTS();
	}


#else

	int main(int argc, char *argv [])
	{
		xig::enviroment enviroment = xig::get_global_enviroment();

		try {
			xig::evaluate(enviroment, xig::parser::from_file(argv[1]));
		} catch (xig::error e) {
			e.print_default_message();
		}
		
	}

#endif
