#include "stdlib.hpp"

namespace xig
{
	enviroment get_global_enviroment()
	{
		enviroment enviroment(env_type::Namespace);

	// core
		enviroment.set("=", data(data_type::Function, function(stdlib::define())));

		enviroment.set("fn", data(data_type::Function, function(stdlib::create_lambda())));

		enviroment.set("if", data(data_type::Function, function(stdlib::if_expression())));

		enviroment.set("let", data(data_type::Function, function(stdlib::let_expression())));

		enviroment.set("println", data(data_type::Function, function(stdlib::print_line())));

		enviroment.set("get-input", data(data_type::Function, function(stdlib::get_input())));

		enviroment.set("apply", data(data_type::Function, function(stdlib::apply())));

		enviroment.set("map", data(data_type::Function, function(stdlib::map())));

		enviroment.set("part", data(data_type::Function, function(stdlib::partial())));

	// math

		enviroment.set("+", data(data_type::Function, function(stdlib::add())));

		enviroment.set("-", data(data_type::Function, function(stdlib::minus())));

		enviroment.set("/", data(data_type::Function, function(stdlib::divide())));

		enviroment.set("*", data(data_type::Function, function(stdlib::multiply())));

		enviroment.set(">", data(data_type::Function, function(stdlib::greater_than())));

		enviroment.set("<", data(data_type::Function, function(stdlib::less_than())));

		enviroment.set("==", data(data_type::Function, function(stdlib::equal_to())));
	
	//string

		enviroment.set("string", data(data_type::Function, function(stdlib::concatinate())));

	//boolean

		enviroment.set("not", data(data_type::Function, function(stdlib::boolean_not())));

	//tuple

		enviroment.set("join", data(data_type::Function, function(stdlib::join())));

		enviroment.set("unique", data(data_type::Function, function(stdlib::unique())));

		enviroment.set("first", data(data_type::Function, function(stdlib::first())));

		enviroment.set("last", data(data_type::Function, function(stdlib::last())));

		enviroment.set("range", data(data_type::Function, function(stdlib::range())));

	//containers

		enviroment.set("at", data(data_type::Function, function(stdlib::at())));

		enviroment.set("size", data(data_type::Function, function(stdlib::size())));

		return enviroment;
	}
}
