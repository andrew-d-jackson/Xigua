#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class symbol : public data {
private:
  std::string value;

public:
  symbol(std::string value) : value(value) {}
  virtual ~symbol() {}

  virtual data_type type() const { return data_type::symbol; };

  virtual const symbol &as_symbol() const { return *this; }

  operator std::string() const { return value; }
  std::string as_std_string() const { return value; }

  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return (value < other.as_symbol().value);
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const {
    if (type() == other.type())
      return (value == other.as_symbol().value);
    return false;
  }
};

extern data_ptr make_symbol(std::string str);
}
