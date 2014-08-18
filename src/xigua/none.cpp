#include "xigua/none.hpp"

namespace xig {

data_type none::type() const { return data_type::none; };

const none &none::as_none() const { return *this; }

bool none::operator<(const data &other) const {
  if (type() == other.type())
    return false;
  return type() < other.type();
}

bool none::operator==(const data &other) const {
  if (type() == other.type())
    return true;
  return false;
}

data_ptr make_none() { return std::make_shared<none>(); }
}
