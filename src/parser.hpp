#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "helpers.hpp"
#include "datatype.hpp"
#include "error.hpp"


namespace Xigua
{

	class Parser {
	public:
		DataType from_file(const std::string file_location) const;
		DataType from_string(const std::string source_code) const;

	private:

		std::string read_file(const std::string file_location) const;

		std::vector<std::string> source_to_string_list(const std::string source_code) const;
		void validate_string_list(const std::vector<std::string> string_list) const;

		DataType string_list_to_data_type(const std::vector<std::string> string_list, const DataTypes list_type = DataTypes::Proc) const;
		DataType string_to_data_type(const std::string input_string) const;
	};

}
