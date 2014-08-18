#pragma once

#include <memory>

#include "xigua/data.hpp"

namespace xig {

class decimal : public data {
private:
  long double value;

public:
  decimal(long double value) : value(value) {}
  virtual ~decimal() {}

  virtual data_type type() const;

  virtual const decimal &as_decimal() const;

  operator double() const;
  long double as_double() const;

  virtual bool operator<(const data &other) const;
  virtual bool operator==(const data &other) const;
};

extern data_ptr make_decimal(long double num);
}
