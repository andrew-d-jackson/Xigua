#include "gtest/gtest.h"
#include "xigua/xigua.hpp"
#include "xigua/stdlib.hpp"

using namespace xig;

TEST(Standard_Library_String, Concatinate) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(
      *evaluate(env, parser::from_string("[string \"hello \" \"world\"]")),
      *make_string("hello world"));

  EXPECT_EQ(*evaluate(env, parser::from_string("[string 2]")),
            *make_string("2"));

  EXPECT_EQ(*evaluate(env, parser::from_string("[string 2 2]")),
            *make_string("22"));

  EXPECT_EQ(*evaluate(env, parser::from_string("[string \"hello\"2]")),
            *make_string("hello2"));
}

TEST(Standard_Library_String, SubString) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[substr \"hello world\" 1 3]")),
            *make_string("ell"));

  EXPECT_EQ(*evaluate(env, parser::from_string("[substr \"hello world\" 2 5]")),
            *make_string("llo "));

  EXPECT_EQ(*evaluate(env, parser::from_string("[substr \"hello world\" 2 2]")),
            *make_string("l"));
}
