#include "xigua/process.hpp"

namespace xig {

data_ptr make_process(std::vector<data_ptr> val) {
  return std::make_shared<process>(val);
}
}
