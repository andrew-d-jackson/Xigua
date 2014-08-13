#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class map : public data {
private:
  std::map<data_ptr, data_ptr> value;

public:
  map(std::map<data_ptr, data_ptr> value) : value(value) {}
  virtual ~map() {}

  virtual data_type type() const { return data_type::map; };

  virtual const map &as_map() const { return *this; }

  operator std::map<data_ptr, data_ptr>() const { return value; }
  std::map<data_ptr, data_ptr> as_std_map() const { return value; }

  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return (value < other.as_map().value);
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const {
    if (type() == other.type())
      return (value == other.as_map().value);
    return false;
  }
};

extern data_ptr make_map(std::map<data_ptr, data_ptr> val);
extern data_ptr make_map(std::vector<data_ptr> val);
}
