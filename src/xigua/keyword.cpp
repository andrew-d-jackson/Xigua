#include "xigua/keyword.hpp"

namespace xig {

data_ptr make_keyword(std::string str) {
  return std::make_shared<keyword>(str);
}
}
