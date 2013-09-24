#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace Xigua
{
	enum class ErrorTypes { UNMATCHING_BRACKETS, INVALID_ARGS, };
	class Error {
	private:
		ErrorTypes error_type;
		std::string descripton;
		std::vector<std::string> function_call_list;

	public:
		Error(ErrorTypes error_type, std::string descripton, std::vector<std::string> function_call_list)
			: error_type(error_type), descripton(descripton), function_call_list(function_call_list) {}

		//ErrorTypes get_error_type() const;
		//std::string get_description() const;
		//std::vector<std::string> get_function_call_list() const;
		//std::map<std::string, DataType> get_enviroment_variables() const;

		void print() const {
			std::cout << "Error: " << (int)error_type << std::endl;

			std::cout << "Description: " << descripton << std::endl;

			std::cout << "Function Call List: root";
			for (auto f_name : function_call_list) {
				std::cout << " -> " << f_name;
			}
			std::cout << std::endl;
		};
	};

}
