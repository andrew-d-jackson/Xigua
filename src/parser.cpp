#include "parser.hpp"


namespace Xigua
{
	DataType Parser::parse_to_data_types(std::vector<std::string> string_list, DataTypes list_type)
	{
		std::vector<DataType> data;
		for (unsigned int index = 0; index < string_list.size(); ++index)
		{
			if (string_list.at(index) == "[" || string_list.at(index) == "{" || string_list.at(index) == "#{")
			{
				DataTypes sub_list_type = DataTypes::Proc;
				if (string_list.at(index) == "{"){
					sub_list_type = DataTypes::Tuple;
				} else if (string_list.at(index) == "#{"){
					sub_list_type = DataTypes::HashMap;
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
				data.push_back(parse_to_data_types(sub_list, sub_list_type));
			}
			else
			{
				data.push_back(string_to_data(string_list.at(index)));
			}
		}
		return DataType(list_type, data);
	}

	DataType Parser::string_to_data(std::string input_string)
	{
		if (is_number(input_string))
		{
			DataType data(DataTypes::Number, (long double)atof(input_string.c_str()));
			return data;
		}
		else if (input_string[0] == '"')
		{
			DataType data(DataTypes::String, input_string.substr(1, input_string.size() - 2));
			return data;
		}
		else if (input_string == "true" || input_string == "false")
		{
			DataType data(DataTypes::Bool);
			if (input_string == "true")
				data.boolean(true);
			else
				data.boolean(false);

			return data;
		}
		else
		{
			DataType data(DataTypes::Symbol, input_string);
			return data;
		}
	}


	Parser::Parser(std::string program_string)
	{
		raw_string = program_string;
	}

	std::vector<std::string> Parser::as_string_list()
	{
		std::vector<std::string> parsed_list;

		bool is_reading_string = false;
		bool is_commenting = false;
		std::stringstream string_buffer;
		bool string_buffer_contains_data = false;
		for (unsigned int index(0); index < raw_string.size(); index++)
		{
			char c = raw_string.at(index);
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
				else if (c == '#' && raw_string.at(index+1) == '{')
				{
					if (!is_reading_string) {
					    if (string_buffer_contains_data) {
					    	parsed_list.push_back(string_buffer.str());
					    	string_buffer.str("");
					    	string_buffer_contains_data = false;
					    }
					    parsed_list.push_back(std::string("#{"));
	                } else {
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
		}


		return parsed_list;
	}

	DataType Parser::as_data_type()
	{
		return parse_to_data_types(as_string_list());
	}

}
