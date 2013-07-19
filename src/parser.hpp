#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "helpers.hpp"
#include "datatype.hpp"

namespace Xigua
{
	class Parser
	{
	private:
		std::string raw_string;

		DataType parse_to_data_types(std::vector<std::string> string_list, DataTypes list_type = DataTypes::Proc);

	public:
		Parser(std::string program_string);

		std::vector<std::string> as_string_list();
		DataType as_data_type();
	};
}