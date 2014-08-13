#pragma once

#include <iostream>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class integer : public data {
private:
  long long value;

public:
  integer(long long value) : value(value) {}
  virtual ~integer() {}

  virtual data_type type() const { return data_type::integer; };

  virtual const integer &as_integer() const { return *this; }

  operator int() const { return value; }
  long long as_int() const { return value; }

  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return (value < other.as_integer().value);
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const {
    if (type() == other.type())
      return (value == other.as_integer().value);
    return false;
  }
};

extern data_ptr make_integer(long long num);
}
