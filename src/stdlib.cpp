#include "stdlib.hpp"

namespace xig
{
	enviroment get_global_enviroment()
	{
		enviroment enviroment(env_type::Namespace);

	// core

		enviroment.set("=", {data_type::Function, function(method(2, false, false, &stdlib::define))}, true);

		enviroment.set("fn", {data_type::Function, function(method(2, false, false, &stdlib::create_lambda))}, true);

		enviroment.set("if", {data_type::Function, function(method(3, false, false, &stdlib::if_expression))}, true);

		enviroment.set("let", {data_type::Function, function(method(2, false, false, &stdlib::let_expression))}, true);

		enviroment.set("println", {data_type::Function, function(method(1, false, &stdlib::print_line))}, true);

		enviroment.set("get-input", {data_type::Function, function(method(0, false, &stdlib::get_input))}, true);

		enviroment.set("apply", {data_type::Function, function(method(2, false, &stdlib::apply))}, true);

		enviroment.set("map", {data_type::Function, function(method(2, true, &stdlib::map))}, true);

		enviroment.set("part", {data_type::Function, function(method(2, true, &stdlib::partial))}, true);

	// math

		enviroment.set("+", {data_type::Function, function(method(2, true, &stdlib::add))}, true);

		enviroment.set("-", {data_type::Function, function(method(2, true, &stdlib::minus))}, true);

		enviroment.set("*", {data_type::Function, function(method(2, true, &stdlib::multiply))}, true);

		enviroment.set("/", {data_type::Function, function(method(2, true, &stdlib::divide))}, true);

		enviroment.set(">", {data_type::Function, function(method(2, true, &stdlib::greater_than))}, true);

		enviroment.set("<", {data_type::Function, function(method(2, true, &stdlib::less_than))}, true);

		enviroment.set("==", {data_type::Function, function(method(2, true, &stdlib::equal_to))}, true);

	//string

		enviroment.set("string", {data_type::Function, function(method(1, true, &stdlib::concatinate))}, true);

	//boolean

		enviroment.set("not", {data_type::Function, function(method(1, false, &stdlib::boolean_not))}, true);

	//tuple

		enviroment.set("join", {data_type::Function, function(method(2, true, &stdlib::join))}, true);

		enviroment.set("unique", {data_type::Function, function(method(1, false, &stdlib::unique))}, true);

		enviroment.set("first", {data_type::Function, function(method(1, false, &stdlib::first))}, true);

		enviroment.set("last", {data_type::Function, function(method(1, false, &stdlib::last))}, true);

		enviroment.set("range", {data_type::Function, function(method(3, false, &stdlib::range))}, true);

	//containers

		enviroment.set("at", {data_type::Function, function(method(2, false, &stdlib::at))}, true);

		enviroment.set("size", {data_type::Function, function(method(1, false, &stdlib::size))}, true);

		return enviroment;
	}
}
