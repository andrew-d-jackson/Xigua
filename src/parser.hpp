#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "data.hpp"
#include "error.hpp"


namespace xig {

	class parser {
	public:
		data from_file(const std::string file_location) const;
		data from_string(const std::string source_code) const;

	private:
		std::string read_file(const std::string file_location) const;

		std::vector<std::string> source_to_string_list(const std::string source_code) const;
		void validate_string_list(const std::vector<std::string> string_list) const;

		data string_list_to_data_type(const std::vector<std::string> string_list, const data_type list_type = data_type::process) const;
		data string_to_data_type(const std::string input_string) const;
		bool is_number(std::string string) const;
	};

}
