#include "xigua/decimal.hpp"

namespace xig {

data_ptr make_decimal(long double num) {
  return std::make_shared<decimal>(num);
}
}
