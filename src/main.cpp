#include <iostream>

#include "enviroment.hpp"
#include "stdlib.hpp"
#include "parser.hpp"
#include "error.hpp"
#include "evaluate.hpp"


int main(int argc, char *argv [])
{
	xig::parser parser;
	xig::enviroment enviroment = xig::get_global_enviroment();

	try {
		xig::evaluate(enviroment, parser.from_file(argv[1]));
//		xig::evaluate(enviroment, parser.from_string("[println \"Hello World\"]"));
	} catch (xig::error e) {
		e.print_default_message();
	}
	
}