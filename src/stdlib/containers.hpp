#pragma once

#include <vector>

#include "../datatype.hpp"
#include "../enviroment.hpp"
#include "../error.hpp"

#include "utils.hpp"

namespace xig {
namespace stdlib {

	extern data at(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);
	
	extern data size(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

}}
