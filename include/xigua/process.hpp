#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

#include "xigua/tuple.hpp"

namespace xig {

class process : public tuple {
public:
  using tuple::tuple;
  virtual ~process() {}

  virtual data_type type() const { return data_type::process; };
  virtual const process &as_process() const { return *this; }
  virtual const tuple &as_tuple() const { throw; }
};

extern data_ptr make_process(std::vector<data_ptr> val);
}
