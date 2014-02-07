#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace xig {

	enum class error_types { unmatching_brackets, invalid_arguments, };

	class error {
	private:
		error_types error_type;
		std::string descripton;
		std::vector<std::string> function_call_list;

	public:
		error(error_types error_type, std::string descripton, std::vector<std::string> function_call_list);

		error_types get_error_type() const;
		std::string get_description() const;
		std::vector<std::string> get_function_call_list() const;

		void print_default_message() const;
	};

}
