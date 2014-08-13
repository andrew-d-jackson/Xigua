#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

#include "xigua/tuple.hpp"

namespace xig {

class process : public base_tuple {
public:
  using base_tuple::base_tuple;
  virtual ~process() {}

  virtual data_type type() const { return data_type::process; }
  virtual const process &as_process() const { return *this; }
};

extern data_ptr make_process(std::vector<data_ptr> val);
}
