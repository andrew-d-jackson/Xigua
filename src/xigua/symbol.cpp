#include "xigua/symbol.hpp"

namespace xig {

data_ptr make_symbol(std::string str) { return std::make_shared<symbol>(str); }
}
