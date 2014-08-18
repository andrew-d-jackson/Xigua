#include "xigua/process.hpp"

namespace xig {

data_type process::type() const { return data_type::process; }

const process &process::as_process() const { return *this; }

data_ptr make_process(std::vector<data_ptr> val) {
  return std::make_shared<process>(val);
}
}
