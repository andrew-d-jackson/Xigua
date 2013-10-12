#pragma once

#include "datatype.hpp"
#include "enviroment.hpp"

#include "functions/core.hpp"
#include "functions/math.hpp"
#include "functions/boolean.hpp"
#include "functions/string.hpp"
#include "functions/tuple.hpp"
#include "functions/containers.hpp"

namespace xig
{
	enviroment get_global_enviroment()
	{
		enviroment enviroment(env_type::Namespace);

	// core

		enviroment.set("=", {data_type::Function, function(method(2, false, false, &Functions::Core::define))}, true);

		enviroment.set("fn", {data_type::Function, function(method(2, false, false, &Functions::Core::create_lambda))}, true);

		enviroment.set("if", {data_type::Function, function(method(3, false, false, &Functions::Core::if_expression))}, true);

		enviroment.set("let", {data_type::Function, function(method(2, false, false, &Functions::Core::let_expression))}, true);

		enviroment.set("println", {data_type::Function, function(method(1, false, &Functions::Core::print_line))}, true);

		enviroment.set("get-input", {data_type::Function, function(method(0, false, &Functions::Core::get_input))}, true);

		enviroment.set("apply", {data_type::Function, function(method(2, false, &Functions::Core::apply))}, true);

		enviroment.set("map", {data_type::Function, function(method(2, true, &Functions::Core::map))}, true);

		enviroment.set("part", {data_type::Function, function(method(2, true, &Functions::Core::partial))}, true);

	// math

		enviroment.set("+", {data_type::Function, function(method(2, true, &Functions::Math::add))}, true);

		enviroment.set("-", {data_type::Function, function(method(2, true, &Functions::Math::minus))}, true);

		enviroment.set("*", {data_type::Function, function(method(2, true, &Functions::Math::multiply))}, true);

		enviroment.set("/", {data_type::Function, function(method(2, true, &Functions::Math::divide))}, true);

		enviroment.set(">", {data_type::Function, function(method(2, true, &Functions::Math::greater_than))}, true);

		enviroment.set("<", {data_type::Function, function(method(2, true, &Functions::Math::less_than))}, true);

		enviroment.set("==", {data_type::Function, function(method(2, true, &Functions::Math::equal_to))}, true);

	//string

		enviroment.set("string", {data_type::Function, function(method(1, true, &Functions::String::concatinate))}, true);

	//boolean

		enviroment.set("not", {data_type::Function, function(method(1, false, &Functions::Boolean::boolean_not))}, true);

	//tuple

		enviroment.set("join", {data_type::Function, function(method(2, true, &Functions::Tuple::join))}, true);

		enviroment.set("unique", {data_type::Function, function(method(1, false, &Functions::Tuple::unique))}, true);

		enviroment.set("first", {data_type::Function, function(method(1, false, &Functions::Tuple::first))}, true);

		enviroment.set("last", {data_type::Function, function(method(1, false, &Functions::Tuple::last))}, true);

		enviroment.set("range", {data_type::Function, function(method(3, false, &Functions::Tuple::range))}, true);

	//containers

		enviroment.set("at", {data_type::Function, function(method(2, false, &Functions::Containers::at))}, true);

		enviroment.set("size", {data_type::Function, function(method(1, false, &Functions::Containers::size))}, true);

		return enviroment;
	}
}
