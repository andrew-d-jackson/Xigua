#include "gtest/gtest.h"
#include "xigua/xigua.hpp"

using namespace xig;

TEST(Standard_Library_Function, Fn) {
  enviroment env = get_global_enviroment();
  evaluate(env, parser::from_string("[= add [fn (a b) [+ a b]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[add 1 1]")), make_number(2));

  evaluate(env, parser::from_string("[= multi [fn (a) [1] (a b) [2]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[multi 1]")), make_number(1));
  EXPECT_EQ(evaluate(env, parser::from_string("[multi 1 1]")), make_number(2));
}

TEST(Standard_Library_Function, ConditionalArgs) {
  enviroment env = get_global_enviroment();
  evaluate(env, parser::from_string("[= equal [fn ([== a b]) [a]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[equal 1 1]")), make_number(1));

  evaluate(env, parser::from_string("[= abso [fn ([< i 0]) [- 0 i] (i) [i]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[abso 10]")), make_number(10));
  EXPECT_EQ(evaluate(env, parser::from_string("[abso -11]")), make_number(11));

  evaluate(env, parser::from_string("[= maxi [fn ([> x y]) [x] (x y) [y]]]"));

  EXPECT_EQ(evaluate(env, parser::from_string("[maxi 10 11]")),
            make_number(11));
  EXPECT_EQ(evaluate(env, parser::from_string("[maxi 20 2]")), make_number(20));
  EXPECT_EQ(evaluate(env, parser::from_string("[maxi 20 20]")),
            make_number(20));
}
