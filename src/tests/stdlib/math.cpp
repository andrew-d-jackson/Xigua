#include "gtest/gtest.h"
#include "xigua/xigua.hpp"
#include "xigua/stdlib.hpp"

using namespace xig;

TEST(Standard_Library_Math, Add) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[+ 2 2]")), *make_integer(4));

  EXPECT_EQ(*evaluate(env, parser::from_string("[+ 2.2 4]")),
            *make_decimal(6.2));

  EXPECT_EQ(*evaluate(env, parser::from_string("[+ 0 0]")), *make_integer(0));

  EXPECT_EQ(*evaluate(env, parser::from_string("[+ -2 3]")), *make_integer(1));

  EXPECT_EQ(*evaluate(env, parser::from_string("[+ -2.2 -2.2]")),
            *make_decimal(-4.4));
}

TEST(Standard_Library_Math, Subtract) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[- 10 2]")), *make_integer(8));

  EXPECT_EQ(*evaluate(env, parser::from_string("[- 10 4.2]")),
            *make_decimal(5.8));

  EXPECT_EQ(*evaluate(env, parser::from_string("[- 1 2]")), *make_integer(-1));

  EXPECT_EQ(*evaluate(env, parser::from_string("[- -2 3]")), *make_integer(-5));

  EXPECT_EQ(*evaluate(env, parser::from_string("[- -2.2 -2.2]")),
            *make_decimal(0));
}

TEST(Standard_Library_Math, Multiply) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[* 10 2]")), *make_integer(20));

  EXPECT_EQ(*evaluate(env, parser::from_string("[* 10 4]")), *make_integer(40));

  EXPECT_EQ(*evaluate(env, parser::from_string("[* 1 2]")), *make_integer(2));

  EXPECT_EQ(*evaluate(env, parser::from_string("[* 1 0]")), *make_integer(0));

  EXPECT_EQ(*evaluate(env, parser::from_string("[* 0 0]")), *make_integer(0));
}

TEST(Standard_Library_Math, Divide) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[/ 10 2]")), *make_decimal(5));

  EXPECT_EQ(*evaluate(env, parser::from_string("[/ 10 4]")),
            *make_decimal(2.5));

  EXPECT_EQ(*evaluate(env, parser::from_string("[/ 1 2]")), *make_decimal(0.5));
}

TEST(Standard_Library_Math, Chained_Equations) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[+ [/ 10 2] 2]")),
            *make_decimal(7));

  EXPECT_EQ(*evaluate(env, parser::from_string("[/ [* 5 [- 4 2]] [+ 2 2]]")),
            *make_decimal(2.5));
}

TEST(Standard_Library_Math, Equality) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[== 2 2]")),
            *make_boolean(true));

  EXPECT_EQ(
      *evaluate(env, parser::from_string("[== 2.5 [/ [* 5 [- 4 2]] [+ 2 2]]]")),
      *make_boolean(true));

  EXPECT_EQ(
      *evaluate(env, parser::from_string("[== 3 [/ [* 5 [- 4 2]] [+ 2 2]]]")),
      *make_boolean(false));
}

TEST(Standard_Library_Math, Less_Than) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[< 2 4]")),
            *make_boolean(true));

  EXPECT_EQ(*evaluate(env, parser::from_string("[< 4 2]")),
            *make_boolean(false));

  EXPECT_EQ(*evaluate(env, parser::from_string("[< [+ 2 4] 2]")),
            *make_boolean(false));
}

TEST(Standard_Library_Math, Greater_Than) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[> 2 4]")),
            *make_boolean(false));

  EXPECT_EQ(*evaluate(env, parser::from_string("[> 4 2]")),
            *make_boolean(true));

  EXPECT_EQ(*evaluate(env, parser::from_string("[> [+ 2 4] 2]")),
            *make_boolean(true));
}

TEST(Standard_Library_Math, Modulo) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[% 2 4]")), *make_integer(2));

  EXPECT_EQ(*evaluate(env, parser::from_string("[% 6 4]")), *make_integer(2));

  EXPECT_DOUBLE_EQ(
      evaluate(env, parser::from_string("[% 6 4.2]"))->as_decimal().as_double(),
      1.8);

  EXPECT_DOUBLE_EQ(
      evaluate(env, parser::from_string("[% 6.2 4]"))->as_decimal().as_double(),
      2.2);

  EXPECT_EQ(*evaluate(env, parser::from_string("[% 6.2 4.2]")),
            *make_decimal(2));
}
