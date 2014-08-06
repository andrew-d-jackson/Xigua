#include "gtest/gtest.h"
#include "xigua/xigua.hpp"

using namespace xig;

TEST(Standard_Library_Function, Fn) {
  enviroment env = get_global_enviroment();
  evaluate(env, parser::from_string("[= add [fn (a b) [+ a b]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[add 1 1]")), make_integer(2));

  evaluate(env, parser::from_string("[= multi [fn (a) [1] (a b) [2]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[multi 1]")), make_integer(1));
  EXPECT_EQ(evaluate(env, parser::from_string("[multi 1 1]")), make_integer(2));
}

TEST(Standard_Library_Function, ConditionalArgs) {
  enviroment env = get_global_enviroment();
  evaluate(env, parser::from_string("[= equal [fn ([== a b]) [a]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[equal 1 1]")), make_integer(1));

  evaluate(env, parser::from_string("[= abso [fn ([< i 0]) [- 0 i] (i) [i]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[abso 10]")), make_integer(10));
  EXPECT_EQ(evaluate(env, parser::from_string("[abso -11]")), make_integer(11));

  evaluate(env, parser::from_string("[= maxi [fn ([> x y]) [x] (x y) [y]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[maxi 10 11]")),
            make_integer(11));
  EXPECT_EQ(evaluate(env, parser::from_string("[maxi 20 2]")),
            make_integer(20));
  EXPECT_EQ(evaluate(env, parser::from_string("[maxi 20 20]")),
            make_integer(20));

  evaluate(env, parser::from_string("[= a [fn ([> x [+ x y]]) [x]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[a 4 -2]")), make_integer(4));

  evaluate(env,
           parser::from_string(
               "[= first-two? [fn ([== [first b] 2]) [true] (c) [false]]]"));
  EXPECT_EQ(evaluate(env, parser::from_string("[first-two? 4]")),
            make_boolean(false));
  EXPECT_EQ(evaluate(env, parser::from_string("[first-two? (2 3 5)]")),
            make_boolean(true));
}

TEST(Standard_Library_Function, EqualArgs) {
  enviroment env = get_global_enviroment();
  evaluate(env, parser::from_string("[= isOne [fn (1) [true] (x) [false]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[isOne 1]")),
            make_boolean(true));

  EXPECT_EQ(evaluate(env, parser::from_string("[isOne :pipe]")),
            make_boolean(false));

  EXPECT_EQ(evaluate(env, parser::from_string("[isOne [- 2 1]]")),
            make_boolean(true));

  evaluate(env,
           parser::from_string(
               "[= isPipe [fn (:pipe) [true] (:pipes) [true] (x) [false]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[isPipe :pipe]")),
            make_boolean(true));

  EXPECT_EQ(evaluate(env, parser::from_string("[isPipe :pipes]")),
            make_boolean(true));

  EXPECT_EQ(evaluate(env, parser::from_string("[isPipe 22]")),
            make_boolean(false));
}

TEST(Standard_Library_Function, Recursion) {
  enviroment env = get_global_enviroment();

  evaluate(env, parser::from_string(
                    "[= fac1 [fn (0) [1] (n) [* n [fac1 [- n 1]]]]]"));
  evaluate(env, parser::from_string(
                    "[= fac2 [fn (0) [1] (n) [* [fac2 [- n 1]] n]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[fac1 5]")), make_integer(120));
  EXPECT_EQ(evaluate(env, parser::from_string("[fac2 5]")), make_integer(120));
}
