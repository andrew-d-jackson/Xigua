#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class tuple : public data {
private:
  std::vector<data_ptr> value;

public:
  tuple(std::vector<data_ptr> value) : value(value) {}
  virtual ~tuple() {}

  virtual data_type type() const { return data_type::tuple; };
  virtual const tuple &as_tuple() const { return *this; }

  operator std::vector<data_ptr>() const { return value; }
  std::vector<data_ptr> as_std_vector() const { return value; }

  auto begin() -> decltype(value.cbegin()) const { return value.cbegin(); }
  auto end() -> decltype(value.cend()) const { return value.cend(); }
  const data_ptr &at(std::size_t pos) const { return value.at(pos); }

  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return (value < other.as_tuple().value);
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const {
    if (type() == other.type())
      return (value == other.as_tuple().value);
    return false;
  }
};

extern data_ptr make_tuple(std::vector<data_ptr> val);
}
