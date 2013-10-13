#pragma once

#include <vector>

#include "../data.hpp"
#include "../enviroment.hpp"
#include "../error.hpp"

#include "utils.hpp"

namespace xig {
namespace stdlib {

	extern data concatinate(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);
	
}}