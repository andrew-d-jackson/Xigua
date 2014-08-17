#include "xigua/integer.hpp"
#include "xigua/decimal.hpp"

namespace xig {

data_type integer::type() const { return data_type::integer; };

const integer &integer::as_integer() const { return *this; }

integer::operator int() const { return value; }

long long integer::as_int() const { return value; }

bool integer::operator<(const data &other) const {
  if (type() == other.type())
    return (value < other.as_integer().value);
  return type() < other.type();
}

bool integer::operator==(const data &other) const {
  if (type() == other.type())
    return (value == other.as_integer().value);
  if (data_type::decimal == other.type())
    return (value == other.as_decimal().as_double());
  return false;
}

data_ptr make_integer(long long num) { return std::make_shared<integer>(num); }
}
