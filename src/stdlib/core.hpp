#pragma once

#include <vector>
#include <functional>

#include "../datatype.hpp"
#include "../enviroment.hpp"
#include "../error.hpp"
#include "../evaluate.hpp"

#include "utils.hpp"

namespace xig {
namespace stdlib {
	
	extern data define(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data create_lambda(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data let_expression(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data if_expression(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data print_line(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data get_input(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data map(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data apply(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

	extern data partial(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list);

}}