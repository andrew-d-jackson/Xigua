#pragma once

#include <iostream>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class boolean : public data {
private:
  bool value;

public:
  boolean(bool value) : value(value) {}
  virtual ~boolean() {}

  virtual data_type type() const { return data_type::boolean; };

  virtual const boolean &as_boolean() const { return *this; }

  operator bool() const { return value; }
  bool as_bool() const { return value; }

  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return (value < other.as_boolean().value);
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const {
    if (type() == other.type())
      return (value == other.as_boolean().value);
    return false;
  }
};

extern data_ptr make_boolean(bool b);
}
