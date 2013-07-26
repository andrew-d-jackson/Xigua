#include "parser.hpp"


namespace Xigua
{
	DataType Parser::parse_to_data_types(std::vector<std::string> string_list, DataTypes list_type)
	{
		DataType current_list(list_type);
		for (unsigned int current_item_index = 0; current_item_index < string_list.size(); ++current_item_index)
		{
			if (string_list.at(current_item_index) == "[" || string_list.at(current_item_index) == "{")
			{
				DataTypes sub_list_type = DataTypes::Proc;
				if (string_list.at(current_item_index) == "{")
					sub_list_type = DataTypes::Tuple;

				std::vector<std::string> new_list;
				int internal_lists = 1;
				while (true) {
					current_item_index++;
					if (string_list.at(current_item_index) == "[" || string_list.at(current_item_index) == "{") {
						internal_lists++;
					}
					else if (string_list.at(current_item_index) == "]" || string_list.at(current_item_index) == "}") {
						internal_lists--;
						if (internal_lists == 0) {
							break;
						}
					}
					new_list.push_back(string_list.at(current_item_index));
				}
				current_list.proc_push_back(parse_to_data_types(new_list, sub_list_type));
			}
			else if (is_number(string_list.at(current_item_index)))
			{
				DataType data(DataTypes::Number, (long double)atof(string_list.at(current_item_index).c_str()));

				current_list.proc_push_back(data);
			}
			else if (string_list.at(current_item_index)[0] == '"')
			{
				DataType data(DataTypes::String, string_list.at(current_item_index).substr(1, string_list.at(current_item_index).size() - 2));
				
				current_list.proc_push_back(data);
			}
			else if (string_list.at(current_item_index) == "true" || string_list.at(current_item_index) == "false")
			{
				DataType data(DataTypes::Bool);
				if (string_list.at(current_item_index) == "true")
					data.boolean(true);
				else
					data.boolean(false);

				current_list.proc_push_back(data);
			}
			else
			{
				DataType data(DataTypes::Symbol, string_list.at(current_item_index));
				current_list.proc_push_back(data);
			}
		}
		return current_list;
	}

	Parser::Parser(std::string program_string)
	{
		raw_string = program_string;
	}

	std::vector<std::string> Parser::as_string_list()
	{
		std::vector<std::string> parsed_list;

		bool is_reading_string = false;
		std::stringstream string_buffer;
		bool string_buffer_contains_data = false;
		for (char c : raw_string)
		{
			if (c == '[' || c == ']' || c == '{' || c == '}'){

                if (!is_reading_string) {
				    if (string_buffer_contains_data) {
				    	parsed_list.push_back(string_buffer.str());
				    	string_buffer.str("");
				    	string_buffer_contains_data = false;
				    }
				    parsed_list.push_back(std::string(1, c));
                } else {
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


		return parsed_list;
	}

	DataType Parser::as_data_type()
	{
		return parse_to_data_types(as_string_list());
	}

}
