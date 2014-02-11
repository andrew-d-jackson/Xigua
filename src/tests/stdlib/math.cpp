#include "gtest/gtest.h"
#include "xigua/xigua.hpp"

using namespace xig;

TEST(Standard_Library_Math, Add) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[+ 2 2]")),
  	make_number(4)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[+ 2 4]")),
  	make_number(6)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[+ 0 0]")),
  	make_number(0)
  );
}

TEST(Standard_Library_Math, Subtract) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[- 10 2]")),
  	make_number(8)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[- 10 4]")),
  	make_number(6)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[- 1 2]")),
  	make_number(-1)
  );
}

TEST(Standard_Library_Math, Multiply) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[* 10 2]")),
  	make_number(20)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[* 10 4]")),
  	make_number(40)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[* 1 2]")),
  	make_number(2)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[* 1 0]")),
  	make_number(0)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[* 0 0]")),
  	make_number(0)
  );
}

TEST(Standard_Library_Math, Divide) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[/ 10 2]")),
  	make_number(5)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[/ 10 4]")),
  	make_number(2.5)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[/ 1 2]")),
  	make_number(0.5)
  );
}

TEST(Standard_Library_Math, Chained_Equations) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[+ [/ 10 2] 2]")),
  	make_number(7)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[/ [* 5 [- 4 2]] [+ 2 2]]")),
  	make_number(2.5)
  );
}

TEST(Standard_Library_Math, Equality) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[== 2 2]")),
  	make_boolean(true)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[== 2.5 [/ [* 5 [- 4 2]] [+ 2 2]]]")),
  	make_boolean(true)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[== 3 [/ [* 5 [- 4 2]] [+ 2 2]]]")),
  	make_boolean(false)
  );
}

TEST(Standard_Library_Math, Less_Than) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[< 2 4]")),
  	make_boolean(true)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[< 4 2]")),
  	make_boolean(false)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[< [+ 2 4] 2]")),
  	make_boolean(false)
  );
}

TEST(Standard_Library_Math, Greater_Than) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[> 2 4]")),
  	make_boolean(false)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[> 4 2]")),
  	make_boolean(true)
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[> [+ 2 4] 2]")),
  	make_boolean(true)
  );
}