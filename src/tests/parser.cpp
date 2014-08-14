#include "gtest/gtest.h"
#include "xigua/xigua.hpp"
#include "xigua/stdlib.hpp"

using namespace xig;

TEST(Parser, Types) {
  EXPECT_EQ(*parser::from_string("2"), *make_integer(2));

  EXPECT_EQ(*parser::from_string("\"hello\""), *make_string("hello"));

  EXPECT_EQ(*parser::from_string(":hello"), *make_keyword("hello"));

  EXPECT_EQ(*parser::from_string("hello"), *make_symbol("hello"));

  EXPECT_EQ(*parser::from_string("true"), *make_boolean(true));

  EXPECT_EQ(*parser::from_string("(1 2)"),
            *make_tuple({make_integer(1), make_integer(2)}));
}
