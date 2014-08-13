#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class string : public data {
private:
  std::string value;

public:
  string(std::string value) : value(value) {}
  virtual ~string() {}

  virtual data_type type() const { return data_type::string; };

  virtual const string &as_string() const { return *this; }

  operator std::string() const { return value; }
  std::string as_std_string() const { return value; }

  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return (value < other.as_string().value);
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const {
    if (type() == other.type())
      return (value == other.as_string().value);
    return false;
  }
};

extern data_ptr make_string(std::string str);
}
