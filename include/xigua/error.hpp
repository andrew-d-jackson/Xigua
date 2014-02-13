#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace xig {

	enum class error_type { internal_error, unmatching_brackets, invalid_arguments, parsing_error, };

	class error {
	private:
		error_type my_error_type;
		std::string descripton;
		std::vector<std::string> function_call_list;

	public:
		error(error_type e_type, std::string descripton, std::vector<std::string> function_call_list);

		error_type get_error_type() const;
		std::string get_description() const;
		std::vector<std::string> get_function_call_list() const;

		void print_default_message() const;
	};

}
