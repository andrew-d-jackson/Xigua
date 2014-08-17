#pragma once

#include <memory>

#include "xigua/data.hpp"
#include "xigua/string.hpp"

namespace xig {

class keyword : public base_string {
public:
  using base_string::base_string;
  virtual ~keyword() {}

  virtual data_type type() const;
  virtual const keyword &as_keyword() const;
};

extern data_ptr make_keyword(std::string str);
}
