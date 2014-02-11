#include "gtest/gtest.h"
#include "xigua/xigua.hpp"

using namespace xig;

TEST(Standard_Library_Tuple, Join) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[join {0 1} {2 3}]")),
    make_tuple({make_number(0), make_number(1), make_number(2), make_number(3)})
  );
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[join 0 1 {2 3}]")),
    make_tuple({make_number(0), make_number(1), make_number(2), make_number(3)})
  );
}


TEST(Standard_Library_Tuple, Unique) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[unique {0 2 2 3}]")),
    make_tuple({make_number(0), make_number(2), make_number(3)})
  );
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[unique {0 2 2 2}]")),
    make_tuple({make_number(0), make_number(2)})
  );
}


TEST(Standard_Library_Tuple, First) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[first {0 2 2 3}]")),
    make_number(0)
  );
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[first {3 2 2 3}]")),
    make_number(3)
  );
}

TEST(Standard_Library_Tuple, Last) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[last {0 2 2 3}]")),
    make_number(3)
  );
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[last {3 2 2 0}]")),
    make_number(0)
  );
}

TEST(Standard_Library_Tuple, Range) {
  enviroment env = get_global_enviroment();
  
  EXPECT_EQ(
    evaluate(env, parser::from_string("[range 1 3 1]")),
    make_tuple({make_number(1), make_number(2)})
  );

  EXPECT_EQ(
    evaluate(env, parser::from_string("[range 4 8 2]")),
    make_tuple({make_number(4), make_number(6)})
  );
}
