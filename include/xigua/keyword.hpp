#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class keyword : public data {
private:
  std::string value;

public:
  keyword(std::string value) : value(value) {}
  virtual ~keyword() {}

  virtual data_type type() const { return data_type::keyword; };

  virtual const keyword &as_keyword() const { return *this; }

  operator std::string() const { return value; }
  std::string as_std_string() const { return value; }

  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return (value < other.as_keyword().value);
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const {
    if (type() == other.type())
      return (value == other.as_keyword().value);
    return false;
  }
};

extern data_ptr make_keyword(std::string str);
}
