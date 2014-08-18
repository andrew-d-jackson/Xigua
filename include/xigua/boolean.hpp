#pragma once

#include <memory>

#include "xigua/data.hpp"

namespace xig {

class boolean : public data {
public:
  boolean(bool value) : value(value) {}
  virtual ~boolean() {}

  virtual data_type type() const;
  virtual const boolean &as_boolean() const;

  operator bool() const;
  bool as_bool() const;

  virtual bool operator<(const data &other) const;
  virtual bool operator==(const data &other) const;

private:
  bool value;
};

extern data_ptr make_boolean(bool b);
}
