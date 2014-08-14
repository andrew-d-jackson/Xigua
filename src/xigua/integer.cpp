#include "xigua/integer.hpp"
#include "xigua/decimal.hpp"

namespace xig {

bool integer::operator==(const data &other) const {
  if (type() == other.type())
    return (value == other.as_integer().value);
  if (data_type::decimal == other.type())
    return (value == other.as_decimal().as_double());
  return false;
}

data_ptr make_integer(long long num) { return std::make_shared<integer>(num); }
}
