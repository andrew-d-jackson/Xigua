#include "xigua/boolean.hpp"

namespace xig {

data_ptr make_boolean(bool b) { return std::make_shared<boolean>(b); }
}
