#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class base_tuple : public data {
private:
  std::vector<data_ptr> value;

public:
  base_tuple(std::vector<data_ptr> value) : value(value) {}
  virtual ~base_tuple() {}

  operator std::vector<data_ptr>() const { return value; }
  std::vector<data_ptr> as_std_vector() const { return value; }

  auto begin() -> decltype(value.cbegin()) const { return value.cbegin(); }
  auto end() -> decltype(value.cend()) const { return value.cend(); }
  const data_ptr &at(std::size_t pos) const { return value.at(pos); }

  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return (value < static_cast<const base_tuple &>(other).value);
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const {
    if (type() == other.type())
      return (value == static_cast<const base_tuple &>(other).value);
    return false;
  }
};

class tuple : public base_tuple {
public:
  using base_tuple::base_tuple;
  virtual ~tuple() {}

  virtual data_type type() const { return data_type::tuple; }
  virtual const tuple &as_tuple() const { return *this; }
};

extern data_ptr make_tuple(std::vector<data_ptr> val);
}
