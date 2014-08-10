#pragma once

#include <vector>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"

namespace xig {
namespace stdlib {
namespace utils {

	extern std::vector<data_ptr> parse_arguments(std::vector<data_ptr> arguments,
                                         unsigned int nonrepeating);

	extern bool all_types_are(std::vector<data_ptr> arguments, data_type expected);
}
}
}
