#pragma once

#include <vector>

#include "../data.hpp"
#include "../enviroment.hpp"
#include "../error.hpp"

#include "utils.hpp"

namespace xig {
namespace stdlib {

	extern data less_than(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data greater_than(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data equal_to(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data add(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data minus(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data multiply(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data divide(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

}}