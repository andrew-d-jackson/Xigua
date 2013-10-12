#include <iostream>

#include "datatype.hpp"
#include "enviroment.hpp"
#include "functions.hpp"
#include "parser.hpp"
#include "error.hpp"


int main(int argc, char *argv [])
{
	xig::parser parser;
	xig::Enviroment enviroment = xig::get_global_enviroment();

	try {
		parser.from_file(argv[1]).evaluate(&enviroment);
	} catch (xig::Error e) {
		e.print();
	}
	
}