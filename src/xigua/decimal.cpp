#include "xigua/decimal.hpp"
#include "xigua/integer.hpp"

namespace xig {

bool decimal::operator==(const data &other) const {
  if (type() == other.type())
    return (value == other.as_decimal().value);
  if (data_type::integer == other.type())
    return (value == other.as_integer().as_int());

  return false;
}

data_ptr make_decimal(long double num) {
  return std::make_shared<decimal>(num);
}
}
