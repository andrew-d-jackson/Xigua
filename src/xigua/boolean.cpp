#include "xigua/boolean.hpp"

namespace xig {

data_type boolean::type() const { return data_type::boolean; };

const boolean &boolean::as_boolean() const { return *this; }

boolean::operator bool() const { return value; }

bool boolean::as_bool() const { return value; }

bool boolean::operator<(const data &other) const {
  if (type() == other.type())
    return (value < other.as_boolean().value);
  return type() < other.type();
}

bool boolean::operator==(const data &other) const {
  if (type() == other.type())
    return (value == other.as_boolean().value);
  return false;
}

data_ptr make_boolean(bool b) { return std::make_shared<boolean>(b); }
}
