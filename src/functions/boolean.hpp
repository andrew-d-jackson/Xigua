#pragma once

#include <vector>
#include <string>
#include <functional>
#include <limits>

#include "../datatype.hpp"
#include "../enviroment.hpp"
#include "../functionutils.hpp"
#include "../error.hpp"


namespace xig
{
	namespace Functions
	{
		namespace Boolean
		{

			data boolean_not(std::vector<data> inputs, Enviroment* enviroment, std::vector<std::string> function_call_list)
			{
				if (inputs.at(0).type() != data_type::Bool)
					throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A Boolean", function_call_list);

				return data(data_type::Bool, !(inputs.at(0).boolean()));
			}

		}
	}
}