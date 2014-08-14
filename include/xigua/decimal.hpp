#pragma once

#include <iostream>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class decimal : public data {
private:
  long double value;

public:
  decimal(long double value) : value(value) {}
  virtual ~decimal() {}

  virtual data_type type() const { return data_type::decimal; };

  virtual const decimal &as_decimal() const { return *this; }

  operator double() const { return value; }
  long double as_double() const { return value; }

  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return (value < other.as_decimal().value);
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const;
};

extern data_ptr make_decimal(long double num);
}
