#include "xigua/tuple.hpp"

namespace xig {

data_ptr make_tuple(std::vector<data_ptr> val) {
  return std::make_shared<tuple>(val);
}
}
