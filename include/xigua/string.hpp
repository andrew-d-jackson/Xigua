#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class base_string : public data {
private:
  std::string value;

public:
  base_string(std::string value) : value(value) {}
  virtual ~base_string() {}

  operator std::string() const { return value; }
  std::string as_std_string() const { return value; }

  auto begin() const -> decltype(value.cbegin()) { return value.cbegin(); }
  auto end() const -> decltype(value.cend()) { return value.cend(); }

  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return (value < static_cast<const base_string &>(other).value);
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const {
    if (type() == other.type())
      return (value == static_cast<const base_string &>(other).value);
    return false;
  }
};

class string : public base_string {
public:
  using base_string::base_string;
  virtual ~string() {}

  virtual data_type type() const { return data_type::string; }
  virtual const string &as_string() const { return *this; }
};

extern data_ptr make_string(std::string str);
}
