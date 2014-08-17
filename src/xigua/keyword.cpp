#include "xigua/keyword.hpp"

namespace xig {

data_type keyword::type() const { return data_type::keyword; };

const keyword &keyword::as_keyword() const { return *this; }

data_ptr make_keyword(std::string str) {
  return std::make_shared<keyword>(str);
}
}
