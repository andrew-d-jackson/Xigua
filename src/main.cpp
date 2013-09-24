#include <iostream>

#include "datatype.hpp"
#include "enviroment.hpp"
#include "functions.hpp"
#include "parser.hpp"
#include "helpers.hpp"
#include "error.hpp"


int main(int argc, char *argv [])
{
	std::string file_data = read_file(argv[1]);
	Xigua::Parser parser(file_data);
	Xigua::Enviroment enviroment = Xigua::get_global_enviroment();

	try {
		parser.as_data_type().evaluate(&enviroment);
	} catch (Xigua::Error e) {
		e.print();
	}
	
}