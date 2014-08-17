#include "xigua/decimal.hpp"
#include "xigua/integer.hpp"

namespace xig {

data_type decimal::type() const { return data_type::decimal; };

const decimal &decimal::as_decimal() const { return *this; }

decimal::operator double() const { return value; }

long double decimal::as_double() const { return value; }

bool decimal::operator<(const data &other) const {
  if (type() == other.type())
    return (value < other.as_decimal().value);
  return type() < other.type();
}

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
