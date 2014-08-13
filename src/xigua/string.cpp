#include "xigua/string.hpp"

namespace xig {

data_ptr make_string(std::string str) { return std::make_shared<string>(str); }
}
