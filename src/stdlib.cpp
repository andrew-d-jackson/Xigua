#include "stdlib.hpp"

namespace xig
{
	enviroment get_global_enviroment()
	{
		enviroment enviroment(env_type::Namespace);

	// core
		enviroment.set("=", data(data_type::function, function(stdlib::define())));

		enviroment.set("fn", data(data_type::function, function(stdlib::create_lambda())));

		enviroment.set("if", data(data_type::function, function(stdlib::if_expression())));

		enviroment.set("let", data(data_type::function, function(stdlib::let_expression())));

		enviroment.set("println", data(data_type::function, function(stdlib::print_line())));

		enviroment.set("get-input", data(data_type::function, function(stdlib::get_input())));

		enviroment.set("apply", data(data_type::function, function(stdlib::apply())));

		enviroment.set("map", data(data_type::function, function(stdlib::map())));

		enviroment.set("part", data(data_type::function, function(stdlib::partial())));

	// math

		enviroment.set("+", data(data_type::function, function(stdlib::add())));

		enviroment.set("-", data(data_type::function, function(stdlib::minus())));

		enviroment.set("/", data(data_type::function, function(stdlib::divide())));

		enviroment.set("*", data(data_type::function, function(stdlib::multiply())));

		enviroment.set(">", data(data_type::function, function(stdlib::greater_than())));

		enviroment.set("<", data(data_type::function, function(stdlib::less_than())));

		enviroment.set(">=", data(data_type::function, function(stdlib::greater_than_or_equal())));

		enviroment.set("<=", data(data_type::function, function(stdlib::less_than_or_equal())));

		enviroment.set("==", data(data_type::function, function(stdlib::equal_to())));
	
	//string

		enviroment.set("string", data(data_type::function, function(stdlib::concatinate())));

	//boolean

		enviroment.set("not", data(data_type::function, function(stdlib::boolean_not())));

	//tuple

		enviroment.set("join", data(data_type::function, function(stdlib::join())));

		enviroment.set("unique", data(data_type::function, function(stdlib::unique())));

		enviroment.set("first", data(data_type::function, function(stdlib::first())));

		enviroment.set("last", data(data_type::function, function(stdlib::last())));

		enviroment.set("range", data(data_type::function, function(stdlib::range())));

	//containers

		enviroment.set("at", data(data_type::function, function(stdlib::at())));

		enviroment.set("size", data(data_type::function, function(stdlib::size())));

		return enviroment;
	}
}
