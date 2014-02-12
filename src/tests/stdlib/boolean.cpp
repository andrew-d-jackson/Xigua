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

  EXPECT_EQ(
    evaluate(env, parser::from_string("[not [== 2 2]]")),
    make_boolean(false)
  );
}

TEST(Standard_Library_Boolean, And) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[and true true]")),
  	make_boolean(true)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[and true true true true]")),
  	make_boolean(true)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[and false false]")),
  	make_boolean(false)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[and true false]")),
  	make_boolean(false)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[and [== 2 2] false]")),
  	make_boolean(false)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[and true true true false]")),
  	make_boolean(false)
  );
}

TEST(Standard_Library_Boolean, Or) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[or true true]")),
  	make_boolean(true)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[or true true true true]")),
  	make_boolean(true)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[or false false false]")),
  	make_boolean(false)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[or false false]")),
  	make_boolean(false)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[or [== 2 2] false]")),
  	make_boolean(true)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[or true false true false]")),
  	make_boolean(true)
  );
}