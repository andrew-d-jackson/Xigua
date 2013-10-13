#include "boolean.hpp"


namespace xig {
namespace stdlib {

	data boolean_not(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		if (inputs.at(0).type() != data_type::Bool)
			throw xig::error(xig::error_types::invalid_arguments, "Not A Boolean", function_call_list);

		return data(data_type::Bool, !(inputs.at(0).boolean()));
	}

}}