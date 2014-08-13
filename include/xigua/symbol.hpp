#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"
#include "xigua/string.hpp"

namespace xig {

class symbol : public string {
public:
  using string::string;
  virtual ~symbol() {}

  virtual data_type type() const { return data_type::symbol; };
  virtual const symbol &as_symbol() const { return *this; }
  virtual const string &as_string() const { throw; }
};

extern data_ptr make_symbol(std::string str);
}
