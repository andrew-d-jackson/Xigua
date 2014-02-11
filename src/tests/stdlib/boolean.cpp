#include "gtest/gtest.h"
#include "xigua/xigua.hpp"

using namespace xig;

TEST(Standard_Library_Boolean, Not) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[not true]")),
  	make_boolean(false)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[not false]")),
    make_boolean(true)
  );
}