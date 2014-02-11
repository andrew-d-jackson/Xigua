#include "gtest/gtest.h"
#include "xigua/xigua.hpp"

using namespace xig;

TEST(Standard_Library_Core, Define) {
  enviroment env = get_global_enviroment();
  evaluate(env, parser::from_string("[= i 2]"));
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[i]")),
    make_number(2)
  );
  
  evaluate(env, parser::from_string("[= i \"hello\"]"));

  EXPECT_EQ(
    evaluate(env, parser::from_string("[i]")),
    make_string("hello")
  );
}

TEST(Standard_Library_Core, Fn) {
  enviroment env = get_global_enviroment();
  evaluate(env, parser::from_string("[= add [fn {a b} [+ a b]]]"));
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[add 1 1]")),
    make_number(2)
  );
}

TEST(Standard_Library_Core, Macro) {
  enviroment env = get_global_enviroment();
  evaluate(env, parser::from_string("[= =fn [macro {name args proc} [= name [fn args proc]]]]"));
  evaluate(env, parser::from_string("[=fn add {a b} [+ a b]]"));
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[add 1 1]")),
    make_number(2)
  );
}


TEST(Standard_Library_Core, If) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[if true 2 4]")),
    make_number(2)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[if false 2 4]")),
    make_number(4)
  );
}


TEST(Standard_Library_Core, Let) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[let #{my-var 3} [3]]")),
    make_number(3)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[= my-var 2][let #{my-var 3} [3]][my-var]")),
    make_number(2)
  );

}

TEST(Standard_Library_Core, Apply) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[apply + {2 2 2 2}]")),
    make_number(8)
  );
}

TEST(Standard_Library_Core, Map) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[map {1 2} {2 2} +]")),
    make_tuple({make_number(3), make_number(4)})
  );
}


TEST(Standard_Library_Core, Partial) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[[part + 2] 4]")),
    make_number(6)
  );
}

