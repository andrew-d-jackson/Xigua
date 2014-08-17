#pragma once

#include <memory>

#include "xigua/data.hpp"
#include "xigua/string.hpp"

namespace xig {

class symbol : public base_string {
public:
  using base_string::base_string;
  virtual ~symbol() {}

  virtual data_type type() const;
  virtual const symbol &as_symbol() const;
};

extern data_ptr make_symbol(std::string str);
}
