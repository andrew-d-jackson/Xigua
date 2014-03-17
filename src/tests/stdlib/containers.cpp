#include <map>

#include "gtest/gtest.h"
#include "xigua/xigua.hpp"

using namespace xig;

TEST(Standard_Library_Conatiners, At) {
  enviroment env = get_global_enviroment();

  EXPECT_EQ(evaluate(env, parser::from_string("[at 2 (0 1 2 3 4 5)]")),
            make_number(2));

  EXPECT_EQ(evaluate(env, parser::from_string("[at 0 (4 4 5 3 4 5)]")),
            make_number(4));

  EXPECT_EQ(evaluate(env, parser::from_string("[at :hello {:hello 1 :bye 3}]")),
            make_number(1));
}

TEST(Standard_Library_Conatiners, Size) {
  enviroment env = get_global_enviroment();

  EXPECT_EQ(evaluate(env, parser::from_string("[size (0 1 2 3 4 5)]")),
            make_number(6));

  EXPECT_EQ(evaluate(env, parser::from_string("[size {:hello 1 :bye 3}]")),
            make_number(2));
}

TEST(Standard_Library_Conatiners, Insert) {
  enviroment env = get_global_enviroment();

  EXPECT_EQ(evaluate(env, parser::from_string("[insert (1 2) 3]")),
            make_tuple({ make_number(1), make_number(2), make_number(3) }));

  auto expected_map = std::map<data, data>();
  expected_map[make_number(1)] = make_number(2);
  expected_map[make_number(3)] = make_number(4);
  EXPECT_EQ(evaluate(env, parser::from_string("[insert {1 2} 3 4]")),
            make_map(expected_map));
}
