#include <iostream>

#include "datatype.hpp"
#include "enviroment.hpp"
#include "functions.hpp"
#include "parser.hpp"
#include "helpers.hpp"
#include "error.hpp"


int main(int argc, char *argv [])
{
	Xigua::Parser parser;
	Xigua::Enviroment enviroment = Xigua::get_global_enviroment();

	try {
		parser.from_file(argv[1]).evaluate(&enviroment);
	} catch (Xigua::Error e) {
		e.print();
	}
	
}