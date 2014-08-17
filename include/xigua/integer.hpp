#pragma once

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

  virtual data_type type() const;

  virtual const integer &as_integer() const;

  operator int() const;
  long long as_int() const;

  virtual bool operator<(const data &other) const;
  virtual bool operator==(const data &other) const;
};

extern data_ptr make_integer(long long num);
}
