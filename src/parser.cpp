#include "parser.hpp"


namespace xig {

	data parser::from_file(const std::string file_location) {

		std::string source_code = read_file(file_location);
		return from_string(source_code);

	}

	data parser::from_string(const std::string source_code) {

		std::vector<std::string> string_list = source_to_string_list(source_code);
		validate_string_list(string_list);
		return string_list_to_data_type(string_list);

	}

	std::string parser::read_file(const std::string file_location) {

		std::ifstream file_stream(file_location.c_str());
		std::stringstream string_buffer;
		string_buffer << file_stream.rdbuf();
		return string_buffer.str();

	}

	std::vector<std::string> parser::source_to_string_list(const std::string source_code) {

		std::vector<std::string> parsed_list;
		bool is_reading_string = false;
		bool is_commenting = false;
		std::stringstream string_buffer;
		bool string_buffer_contains_data = false;

		for (unsigned int index(0); index < source_code.size(); index++)
		{
			char c = source_code.at(index);
			if (is_commenting)
			{
				if (c == '\n')
					is_commenting = false;
			}
			else
			{
				if (c == '~' && !is_reading_string)
				{
					is_commenting = true;
				}
				else if (c == '#' && source_code.at(index + 1) == '{')
				{
					if (!is_reading_string) {
						if (string_buffer_contains_data) {
							parsed_list.push_back(string_buffer.str());
							string_buffer.str("");
							string_buffer_contains_data = false;
						}
						parsed_list.push_back(std::string("#{"));
					}
					else {
						string_buffer << c;
						string_buffer_contains_data = true;
					}
					index++;
				}
				else if (c == '[' || c == ']' || c == '{' || c == '}')
				{

					if (!is_reading_string) {
						if (string_buffer_contains_data) {
							parsed_list.push_back(string_buffer.str());
							string_buffer.str("");
							string_buffer_contains_data = false;
						}
						parsed_list.push_back(std::string(1, c));
					}
					else {
						string_buffer << c;
						string_buffer_contains_data = true;
					}
				}
				else if (c == ' ' || c == '\n' || c == '\t') {

					if (!is_reading_string) {
						if (string_buffer_contains_data) {
							parsed_list.push_back(string_buffer.str());
							string_buffer.str("");
							string_buffer_contains_data = false;
						}
					}
					else {
						string_buffer << c;
						string_buffer_contains_data = true;
					}

				}
				else if (c == '"') {
					string_buffer << '"';
					if (is_reading_string) {
						is_reading_string = false;
						parsed_list.push_back(string_buffer.str());
						string_buffer.str("");
						string_buffer_contains_data = false;
					}
					else {
						is_reading_string = true;
					}

				}
				else {

					string_buffer << c;
					string_buffer_contains_data = true;

				}
			}
		}

		return parsed_list;

	}

	void parser::validate_string_list(const std::vector<std::string> string_list) {

		int closing = 0;
		int opening = 0;

		for (auto token : string_list) {
			if (token == "[")
				opening++;
			else if (token == "]")
				closing++;
		}

		if (opening != closing)
			throw xig::error(xig::error_types::unmatching_brackets, "Amount Of Opening And Closing Brackets Do Not Match", {});
	}

	data parser::string_list_to_data_type(const std::vector<std::string> string_list, const data_type list_type) {

		std::vector<data> current_data;
		for (unsigned int index = 0; index < string_list.size(); ++index)
		{
			if (string_list.at(index) == "[" || string_list.at(index) == "{" || string_list.at(index) == "#{")
			{
				data_type sub_list_type = data_type::process;
				if (string_list.at(index) == "{"){
					sub_list_type = data_type::tuple;
				}
				else if (string_list.at(index) == "#{"){
					sub_list_type = data_type::map;
				}

				std::vector<std::string> sub_list;
				int internal_lists = 1;
				while (true) {
					index++;
					if (string_list.at(index) == "[" || string_list.at(index) == "{" || string_list.at(index) == "#{") {
						internal_lists++;
					}
					else if (string_list.at(index) == "]" || string_list.at(index) == "}") {
						internal_lists--;
						if (internal_lists == 0) {
							break;
						}
					}
					sub_list.push_back(string_list.at(index));
				}
				current_data.push_back(string_list_to_data_type(sub_list, sub_list_type));
			}
			else
			{
				current_data.push_back(string_to_data_type(string_list.at(index)));
			}
		}
		return data(list_type, current_data);

	}

	data parser::string_to_data_type(const std::string input_string) {

		if (is_number(input_string))
		{
			data data(data_type::number, (long double) atof(input_string.c_str()));
			return data;
		}
		else if (input_string[0] == '"')
		{
			data data(data_type::string, input_string.substr(1, input_string.size() - 2));
			return data;
		}
		else if (input_string[0] == ':')
		{
			data data(data_type::keyword, input_string.substr(1, input_string.size() - 1));
			return data;
		}
		else if (input_string == "true" || input_string == "false")
		{
			bool return_value;
			if (input_string == "true")
				return_value = true;
			else
				return_value = false;

			return data(data_type::boolean, return_value);
		}
		else
		{
			data data(data_type::symbol, input_string);
			return data;
		}

	}

	bool parser::is_number(std::string string) {
		
		if (string.size() < 1)
			return false;
			
		for (char c : string) {
			if (!isdigit(c) && c != '.')
				return false;
		}

		return true;
		
	}

}
