#pragma once

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"

namespace xig {

	extern data evaluate(enviroment & env, data input_data, std::vector<std::string> function_call_list = std::vector<std::string>());

}
