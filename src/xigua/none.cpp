#include "xigua/none.hpp"

namespace xig {

data_ptr make_none() { return std::make_shared<none>(); }
}
