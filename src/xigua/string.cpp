#include "xigua/string.hpp"

namespace xig {

base_string::operator std::string() const { return value; }

std::string base_string::as_std_string() const { return value; }

std::string::const_iterator base_string::begin() const {
  return value.cbegin();
}

std::string::const_iterator base_string::end() const { return value.cend(); }

bool base_string::operator<(const data &other) const {
  if (type() == other.type())
    return (value < static_cast<const base_string &>(other).value);
  return type() < other.type();
}

bool base_string::operator==(const data &other) const {
  if (type() == other.type())
    return (value == static_cast<const base_string &>(other).value);
  return false;
}

data_type string::type() const { return data_type::string; }

const string &string::as_string() const { return *this; }

data_ptr make_string(std::string str) { return std::make_shared<string>(str); }
}
