
#include "gtest/gtest.h"

#include "data.hpp"
#include "enviroment.hpp"

using namespace xig;

TEST(Enviroment, Set) {
	enviroment env(env_type::Namespace);
	env.set("test_value", make_number(2));
	EXPECT_EQ(*env.find("test_value"), make_number(2));
	env.set("test_value", make_number(3));
	EXPECT_EQ(*env.find("test_value"), make_number(3));
}

TEST(Enviroment, Parent) {
	enviroment parent(env_type::Namespace);
	enviroment child(env_type::Namespace, &parent);
	EXPECT_TRUE(child.has_parent());
	EXPECT_EQ(child.parent(), &parent);
	parent.set("test_value", make_number(2));
	EXPECT_EQ(*child.find("test_value"), make_number(2));
	child.set("test_value", make_number(3));
	EXPECT_EQ(*child.find("test_value"), make_number(3));
}
