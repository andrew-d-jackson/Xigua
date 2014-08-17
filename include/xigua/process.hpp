#pragma once

#include <memory>

#include "xigua/data.hpp"
#include "xigua/tuple.hpp"

namespace xig {

class process : public base_tuple {
public:
  process(std::vector<data_ptr> value) : base_tuple(value) {}
  virtual ~process() {}

  virtual data_type type() const;
  virtual const process &as_process() const;
};

extern data_ptr make_process(std::vector<data_ptr> val);
}
