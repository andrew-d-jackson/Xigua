#include "xigua/stdlib.hpp"


#include "xigua/stdlib/core.hpp"


#include "xigua/stdlib/math.hpp"
#include "xigua/stdlib/boolean.hpp"
#include "xigua/stdlib/string.hpp"
#include "xigua/stdlib/tuple.hpp"
#include "xigua/stdlib/containers.hpp"
#include "xigua/stdlib/benchmark.hpp"
#include "xigua/stdlib/function.hpp"
#include "xigua/stdlib/types.hpp"
#include "xigua/stdlib/test.hpp"

namespace xig {
enviroment get_global_enviroment() {
  enviroment enviroment(env_type::container);
  
  // core
  enviroment.set("=", make_function(stdlib::define()));

  enviroment.set("fn", make_function(stdlib::create_lambda()));

  enviroment.set("overload", make_function(stdlib::overload()));

  enviroment.set("macro", make_function(stdlib::macro()));

  enviroment.set("import", make_function(stdlib::import()));

  enviroment.set("import-as", make_function(stdlib::import_as()));

  enviroment.set("if", make_function(stdlib::if_expression()));

  enviroment.set("let", make_function(stdlib::let_expression()));

  enviroment.set("println", make_function(stdlib::print_line()));

  enviroment.set("get-input", make_function(stdlib::get_input()));

  enviroment.set("apply", make_function(stdlib::apply()));

  enviroment.set("map", make_function(stdlib::map()));

  enviroment.set("foldl", make_function(stdlib::foldl()));

  enviroment.set("foldr", make_function(stdlib::foldr()));

  enviroment.set("filter", make_function(stdlib::filter()));

  enviroment.set("part", make_function(stdlib::partial()));

  enviroment.set("int", make_function(stdlib::to_integer()));
  
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

  enviroment.set("%", make_function(stdlib::modulo()));

  // string

  enviroment.set("string", make_function(stdlib::concatinate()));

  enviroment.set("substr", make_function(stdlib::substring()));

  // boolean

  enviroment.set("not", make_function(stdlib::boolean_not()));

  enviroment.set("and", make_function(stdlib::boolean_and()));

  enviroment.set("or", make_function(stdlib::boolean_or()));

  // types

  enviroment.set("str?", make_function(stdlib::is_string()));

  enviroment.set("float?", make_function(stdlib::is_decimal()));

  enviroment.set("int?", make_function(stdlib::is_integer()));

  enviroment.set("tuple?", make_function(stdlib::is_tuple()));

  enviroment.set("map?", make_function(stdlib::is_map()));

  enviroment.set("bool?", make_function(stdlib::is_boolean()));

  enviroment.set("none?", make_function(stdlib::is_none()));

  enviroment.set("fn?", make_function(stdlib::is_function()));

  enviroment.set("key?", make_function(stdlib::is_keyword()));

  // tuple

  enviroment.set("join", make_function(stdlib::join()));

  enviroment.set("unique", make_function(stdlib::unique()));

  enviroment.set("first", make_function(stdlib::first()));

  enviroment.set("last", make_function(stdlib::last()));

  enviroment.set("tail", make_function(stdlib::tail()));

  enviroment.set("init", make_function(stdlib::init()));

  enviroment.set("range", make_function(stdlib::range()));

  // containers

  enviroment.set("at", make_function(stdlib::at()));

  enviroment.set("size", make_function(stdlib::size()));

  enviroment.set("insert", make_function(stdlib::insert()));

  // testing

  enviroment.set("test-eq", make_function(stdlib::testeq()));

  enviroment.set("test-ne", make_function(stdlib::testne()));

  enviroment.set("test-tr", make_function(stdlib::testtr()));

  // benchmark

  enviroment.set("bench", make_function(stdlib::benchmark()));
  
  return enviroment;
}
}
