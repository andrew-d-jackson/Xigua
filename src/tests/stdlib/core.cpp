#include "gtest/gtest.h"
#include "xigua/xigua.hpp"
#include "xigua/stdlib.hpp"

using namespace xig;

TEST(Standard_Library_Core, Define) {
  enviroment env = stdlib::get_global_enviroment();
  evaluate(env, parser::from_string("[= i 2]"));

  EXPECT_EQ(*evaluate(env, parser::from_string("[i]")), *make_integer(2));

  evaluate(env, parser::from_string("[= i \"hello\"]"));

  EXPECT_EQ(*evaluate(env, parser::from_string("[i]")), *make_string("hello"));
}

TEST(Standard_Library_Core, Overload) {
  enviroment env = stdlib::get_global_enviroment();
  evaluate(env, parser::from_string("[= f1 [fn (a b) [4]]]"));
  evaluate(env, parser::from_string("[= f2 [overload f1 [fn (a) [6]]]]"));

  EXPECT_EQ(*evaluate(env, parser::from_string("[f2 1 1]")), *make_integer(4));

  EXPECT_EQ(*evaluate(env, parser::from_string("[f2 1]")), *make_integer(6));
}

TEST(Standard_Library_Core, Macro) {
  enviroment env = stdlib::get_global_enviroment();
  evaluate(env,
           parser::from_string(
               "[= =fn [macro (name args proc) [= name [fn args proc]]]]"));
  evaluate(env, parser::from_string("[=fn add (a b) [+ a b]]"));

  EXPECT_EQ(*evaluate(env, parser::from_string("[add 1 1]")), *make_integer(2));
}

TEST(Standard_Library_Core, If) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[if true 2 4]")),
            *make_integer(2));

  EXPECT_EQ(*evaluate(env, parser::from_string("[if false 2 4]")),
            *make_integer(4));
}

TEST(Standard_Library_Core, Let) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[let {my-var 3} [3]]")),
            *make_integer(3));

  EXPECT_EQ(*evaluate(env, parser::from_string(
                               "[= my-var 2][let {my-var 3} [3]][my-var]")),
            *make_integer(2));
}

TEST(Standard_Library_Core, Apply) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[apply + (2 2 2 2)]")),
            *make_integer(8));
}

TEST(Standard_Library_Core, Map) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[map (1 2) (2 2) +]")),
            *make_tuple({make_integer(3), make_integer(4)}));
}

TEST(Standard_Library_Core, Filter) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string(
                               "[filter [fn (i) [== i 2]] (1 2 3 4 2)]")),
            *make_tuple({make_integer(2), make_integer(2)}));

  EXPECT_EQ(*evaluate(env, parser::from_string(
                               "[filter [fn (i) [> i 2]] (1 2 3 4)]")),
            *make_tuple({make_integer(3), make_integer(4)}));
}

TEST(Standard_Library_Core, Partial) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[[part + 2] 4]")),
            *make_integer(6));
}

TEST(Standard_Library_Core, FoldL) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[foldl + 1 (1 2 3)]")),
            *make_integer(7));

  EXPECT_EQ(*evaluate(env, parser::from_string("[foldl / 10 (2 2)]")),
            *make_decimal(2.5));
}

TEST(Standard_Library_Core, FoldR) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[foldr + 1 (1 2 3)]")),
            *make_integer(7));

  EXPECT_EQ(*evaluate(env, parser::from_string("[foldr / 10 (2 2)]")),
            *make_integer(10));
}
