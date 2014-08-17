#pragma once

#include <memory>

#include "xigua/data.hpp"
#include "xigua/tuple.hpp"

namespace xig {

class process : public base_tuple {
public:
  using base_tuple::base_tuple;
  virtual ~process() {}

  virtual data_type type() const;
  virtual const process &as_process() const;
};

extern data_ptr make_process(std::vector<data_ptr> val);
}
