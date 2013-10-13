#include "string.hpp"

namespace xig {
namespace stdlib {

	data concatinate(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		auto arguments = utils::parse_arguments(inputs, 1);

		std::string return_string = "";
		for (auto argument : arguments) {
			return_string += argument.as_string();
		}

		return data(data_type::String, return_string);
	}
}}