#pragma once

#include <iostream>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class none : public data {
public:
  virtual ~none() {}

  virtual data_type type() const { return data_type::none; };

  virtual const none &as_none() const { return *this; }

  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return false;
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const {
    if (type() == other.type())
      return true;
    return false;
  }
};

extern data_ptr make_none();
}
