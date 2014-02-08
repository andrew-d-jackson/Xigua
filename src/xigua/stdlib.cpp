#include "xigua/stdlib.hpp"

#include "xigua/stdlib/core.hpp"
#include "xigua/stdlib/math.hpp"
#include "xigua/stdlib/boolean.hpp"
#include "xigua/stdlib/string.hpp"
#include "xigua/stdlib/tuple.hpp"
#include "xigua/stdlib/containers.hpp"
#include "xigua/stdlib/benchmark.hpp"
#include "xigua/stdlib/test.hpp"

namespace xig
{
	enviroment get_global_enviroment()
	{
		enviroment enviroment(env_type::container);

	// core
		enviroment.set("=", make_function(stdlib::define()));

		enviroment.set("fn", make_function(stdlib::create_lambda()));

		enviroment.set("if", make_function(stdlib::if_expression()));

		enviroment.set("let", make_function(stdlib::let_expression()));

		enviroment.set("println", make_function(stdlib::print_line()));

		enviroment.set("get-input", make_function(stdlib::get_input()));

		enviroment.set("apply", make_function(stdlib::apply()));

		enviroment.set("map", make_function(stdlib::map()));

		enviroment.set("part", make_function(stdlib::partial()));

	// math

		enviroment.set("+", make_function(stdlib::add()));

		enviroment.set("-", make_function(stdlib::minus()));

		enviroment.set("/", make_function(stdlib::divide()));

		enviroment.set("*", make_function(stdlib::multiply()));

		enviroment.set(">", make_function(stdlib::greater_than()));

		enviroment.set("<", make_function(stdlib::less_than()));

		enviroment.set(">=", make_function(stdlib::greater_than_or_equal()));

		enviroment.set("<=", make_function(stdlib::less_than_or_equal()));

		enviroment.set("==", make_function(stdlib::equal_to()));
	
	//string

		enviroment.set("string", make_function(stdlib::concatinate()));

		enviroment.set("substr", make_function(stdlib::substring()));
		
	//boolean

		enviroment.set("not", make_function(stdlib::boolean_not()));

	//tuple

		enviroment.set("join", make_function(stdlib::join()));

		enviroment.set("unique", make_function(stdlib::unique()));

		enviroment.set("first", make_function(stdlib::first()));

		enviroment.set("last", make_function(stdlib::last()));

		enviroment.set("range", make_function(stdlib::range()));

	//containers

		enviroment.set("at", make_function(stdlib::at()));

		enviroment.set("size", make_function(stdlib::size()));

	//testing

		enviroment.set("test-eq", make_function(stdlib::testeq()));
		
		enviroment.set("test-ne", make_function(stdlib::testne()));
		
		enviroment.set("test-tr", make_function(stdlib::testtr()));

	// benchmark

		enviroment.set("bench", make_function(stdlib::benchmark()));


		return enviroment;
	}
}
