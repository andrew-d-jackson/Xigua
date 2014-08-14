#include "gtest/gtest.h"
#include "xigua/xigua.hpp"
#include "xigua/stdlib.hpp"

using namespace xig;

TEST(Standard_Library_Types, Types) {
  enviroment env = stdlib::get_global_enviroment();

  EXPECT_EQ(*evaluate(env, parser::from_string("[bool? false]")),
            *make_boolean(true));

  EXPECT_EQ(*evaluate(env, parser::from_string("[str? \"hello\"]")),
            *make_boolean(true));

  EXPECT_EQ(*evaluate(env, parser::from_string("[int? 200]")),
            *make_boolean(true));

  EXPECT_EQ(*evaluate(env, parser::from_string("[float? 200.0]")),
            *make_boolean(true));

  EXPECT_EQ(*evaluate(env, parser::from_string("[fn? [fn (x) [x]]]")),
            *make_boolean(true));

  EXPECT_EQ(*evaluate(env, parser::from_string("[key? :somekey]")),
            *make_boolean(true));

  EXPECT_EQ(*evaluate(env, parser::from_string("[none? none]")),
            *make_boolean(true));

  EXPECT_EQ(*evaluate(env, parser::from_string("[tuple? (1 2 3)]")),
            *make_boolean(true));

  EXPECT_EQ(*evaluate(env, parser::from_string("[map? {1 2 3 4}]")),
            *make_boolean(true));
}
