#pragma once

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"

namespace xig {

//! Evaluate a process in an enviroment, returns the result of the process
//! @param env the enviroment that the method is bieng run in
//! @param data the process to run or the data to evalute
//! @param fcl the function call list at the time the method was called
extern data evaluate(enviroment &env, data input_data,
                     std::vector<std::string> function_call_list =
                         std::vector<std::string>());
}
