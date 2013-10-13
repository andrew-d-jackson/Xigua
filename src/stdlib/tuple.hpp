#pragma once

#include <vector>
#include <algorithm>

#include "../data.hpp"
#include "../enviroment.hpp"
#include "../error.hpp"

#include "utils.hpp"


namespace xig {
namespace stdlib {

			extern data join(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

			extern data unique(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

			extern data first(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

			extern data last(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

			extern data range(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

}}