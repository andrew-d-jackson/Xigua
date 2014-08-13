#include "xigua/integer.hpp"

namespace xig {

data_ptr make_integer(long long num) { return std::make_shared<integer>(num); }
}
