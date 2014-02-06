
#include "gtest/gtest.h"

#include "data.hpp"

TEST(Data, Equality) {
	EXPECT_TRUE(xig::data(xig::data_type::number, (long double)2.0) == xig::data(xig::data_type::number, (long double)2.0));
}
