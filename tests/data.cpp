
#include "gtest/gtest.h"

#include "data.hpp"

using namespace xig;

TEST(Data, Equality) {
	EXPECT_EQ(make_number(2), make_number(2));
}
