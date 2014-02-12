#include "xigua/data.hpp"

namespace xig
{
	data::data(data_type in_type)
	{
		type(in_type);
	}

	data::data(data_type in_type, std::string string_data)
	{
		type(in_type);
		if (in_type == data_type::string){
			string(string_data);
		} else if (in_type == data_type::symbol){
			symbol(string_data);
		} else if (in_type == data_type::keyword) {
			keyword(string_data);
		} else {
			throw error(error_types::internal_error, "Wrong Data Passed to data::data std::string", {});
		}
	}

	data::data(data_type in_type, long double number_data)
	{
		type(in_type);
		if (in_type == data_type::number){
			number(number_data);
		} else {
			throw error(error_types::internal_error, "Wrong Data Passed to data::data long double", {});
		}
	}

	data::data(data_type in_type, bool boolean_data)
	{
		type(in_type);
		if (in_type == data_type::boolean){
			boolean(boolean_data);
		} else {
			throw error(error_types::internal_error, "Wrong Data Passed to data::data bool", {});
		}
	}

	data::data(data_type in_type, std::vector<data> list_data)
	{
		type(in_type);
		if (in_type == data_type::tuple){
			tuple(list_data);
		} else if (in_type == data_type::process){
			proc(list_data);
		} else if (in_type == data_type::map) {
			hash_map(list_data);
		} else {
			throw error(error_types::internal_error, "Wrong Data Passed to data::data std::vector<data>", {});
		}
	}

	data::data(data_type in_type, std::map<data, data> map_data)
	{
		type(in_type);
		if (in_type == data_type::map){
			hash_map(map_data);
		}  else {
			throw error(error_types::internal_error, "Wrong Data Passed to data::data std::map<data, data>", {});
		}
		
	}

	data::data(data_type in_type, function function_data)
	{
		type(in_type);
		if (in_type == data_type::function){
			functions(function_data);
		}  else {
			throw error(error_types::internal_error, "Wrong Data Passed to data::data function", {});
		}
	}

	data::data(data_type in_type, enviroment container_data)
	{
		type(in_type);
		if (in_type == data_type::container){
			container(container_data);
		}  else {
			throw error(error_types::internal_error, "Wrong Data Passed to data::data enviroment", {});
		}
	}


	bool data::operator==(const data & other) const
	{
		if (type() != other.type())
			return false;

		if (type() == data_type::none)
			return true;

		if (type() == data_type::symbol)
			return (as_symbol() == other.as_symbol());
		
		if (type() == data_type::boolean)
			return (as_boolean() == other.as_boolean());

		if (type() == data_type::string)
			return (as_string() == other.as_string());

		if (type() == data_type::keyword)
			return (as_keyword() == other.as_keyword());

		if (type() == data_type::number)
			return (as_number() == other.as_number());

		if (type() == data_type::tuple)
			return (as_tuple() == other.as_tuple());

		if (type() == data_type::process)
			return false;

		if (type() == data_type::function)
			return false;

		if (type() == data_type::container)
			return false;

		return false;
	}

	bool data::operator!=(const data & other) const
	{
		return !(*this == other);
	}

	bool data::operator<(const data & other) const
	{
		if (type() != other.type())
			return (type() < other.type());

		if (type() == data_type::none)
			return false;

		if (type() == data_type::symbol)
			return (as_symbol() < other.as_symbol());

		if (type() == data_type::keyword)
			return (as_keyword() < other.as_keyword());
		
		if (type() == data_type::boolean)
			return (as_boolean() < other.as_boolean());

		if (type() == data_type::string)
			return (as_string() < other.as_string());

		if (type() == data_type::number)
			return (as_number() < other.as_number());

		if (type() == data_type::tuple)
			return (as_tuple() < other.as_tuple());

		if (type() == data_type::process)
			return false;

		if (type() == data_type::function)
			return false;

		if (type() == data_type::container)
			return false;

		return false;
	}


	data_type data::type() const
	{
		return my_type;
	}

	void data::type(data_type in_type)
	{
		my_type = in_type;

		if (in_type == data_type::none){
			data_pointer = nullptr;
		} else if (in_type == data_type::symbol){
			data_pointer = std::shared_ptr<void>(new std::string());
		} else if (in_type == data_type::boolean){
			data_pointer = std::shared_ptr<void>(new bool(false));
		} else if (in_type == data_type::string){
			data_pointer = std::shared_ptr<void>(new std::string());
		} else if (in_type == data_type::keyword){
			data_pointer = std::shared_ptr<void>(new std::string());
		} else if (in_type == data_type::number){
			data_pointer = std::shared_ptr<void>(new long double(0));
		} else if (in_type == data_type::tuple){
			data_pointer = std::shared_ptr<void>(new std::vector<data>());
		} else if (in_type == data_type::map){
			data_pointer = std::shared_ptr<void>(new std::map<data, data>());
		} else if (in_type == data_type::process){
			data_pointer = std::shared_ptr<void>(new std::vector<data>());
		} else if (in_type == data_type::function){
			data_pointer = std::shared_ptr<void>(new function());
		} else if (in_type == data_type::container){
			data_pointer = std::shared_ptr<void>(new enviroment(env_type::container));
		} else {
			throw error(error_types::internal_error, "Wrong Data Passed to data::type", {});
		}
	}

	std::string data::as_string() const
	{
		return *(static_cast<std::string*>(data_pointer.get()));
	}

	void data::string(std::string in_string)
	{
		data_pointer = std::shared_ptr<void>(new std::string(in_string));
	}

	std::string data::as_keyword() const
	{
		return *(static_cast<std::string*>(data_pointer.get()));
	}

	void data::keyword(std::string in_string)
	{
		data_pointer = std::shared_ptr<void>(new std::string(in_string));
	}

	std::string data::as_symbol() const
	{
		return *(static_cast<std::string*>(data_pointer.get()));
	}
	
	void data::symbol(std::string symbol_name)
	{
		data_pointer = std::shared_ptr<void>(new std::string(symbol_name));
	}

	long double data::as_number() const
	{
		return *(static_cast<long double*>(data_pointer.get()));
	}

	void data::number(long double in_number)
	{
		data_pointer = std::shared_ptr<void>(new long double(in_number));
	}

	std::vector<data> data::as_tuple() const
	{
		return *(static_cast<std::vector<data>*>(data_pointer.get()));
	}

	void data::tuple(std::vector<data> tuple)
	{
		data_pointer = std::shared_ptr<void>(new std::vector<data>(tuple));
	}

	std::map<data, data> data::as_map() const
	{
		return *(static_cast<std::map<data, data>*>(data_pointer.get()));
	}
	
	void data::hash_map(std::map<data, data> in_map)
	{
		data_pointer = std::shared_ptr<void>(new std::map<data, data>(in_map));
	}

	void data::hash_map(std::vector<data> in_list)
	{
		std::map<data, data> temp_map;
		for (unsigned int i(0); i + 1 < in_list.size(); i += 2)
		{
			temp_map[in_list.at(i)] = in_list.at(i + 1);
		}
		hash_map(temp_map);
	}

	std::vector<data> data::as_process() const
	{
		return *(static_cast<std::vector<data>*>(data_pointer.get()));
	}

	void data::proc(std::vector<data> proc)
	{
		data_pointer = std::shared_ptr<void>(new std::vector<data>(proc));
	}

	bool data::as_boolean() const
	{
		return *(static_cast<bool*>(data_pointer.get()));
	}

	void data::boolean(bool in_boolean)
	{
		data_pointer = std::shared_ptr<void>(new bool(in_boolean));
	}

	function data::as_function() const
	{
		return *(static_cast<function*>(data_pointer.get()));
	}

	void data::functions(function in_function)
	{
		data_pointer = std::shared_ptr<void>(new function(in_function));
	}

	enviroment* data::as_container() const
	{
		return (static_cast<enviroment*>(data_pointer.get()));
	}

	void data::container(enviroment in_container)
	{
		data_pointer = std::shared_ptr<void>(new enviroment(in_container));
	}

	std::string string_representation(const data & in_data)
	{
		std::string return_value = "";
		if (in_data.type() == data_type::string) {
			return_value += in_data.as_string();
		}
		else if (in_data.type() == data_type::keyword) {
			return_value += ":" + in_data.as_string();
		}
		else if (in_data.type() == data_type::symbol) {
			return_value += in_data.as_symbol();
		}
		else if (in_data.type() == data_type::boolean){
			if (in_data.as_boolean()) {
				return_value += "true";
			}
			else {
				return_value += "false";
			}
		}
		else if (in_data.type() == data_type::number){
			std::stringstream ss;
			ss << std::fixed;
			ss << in_data.as_number();
			std::string str = ss.str();
			int s;
			for (s = str.length() - 1; s > 0; s--) {
				if (str[s] == '0')
					str.erase(s, 1);
				else
					break;
			}
			if (str[s] == '.')
				str.erase(s, 1);
			return_value += str;
		}
		else if (in_data.type() == data_type::tuple){
			return_value += "{ ";
			for (auto element : in_data.as_tuple()) {
				return_value += string_representation(element);
				return_value += " ";
			}
			return_value += "}";
		}
		else if (in_data.type() == data_type::map){
			return_value += "#{ ";
			for (auto & element : in_data.as_map()) {
				return_value += string_representation(element.first);
				return_value += " => ";
				return_value += string_representation(element.second);
				return_value += ", ";
			}
			return_value += "}";
		}
		else if (in_data.type() == data_type::process){
			return_value += "[ ";
			for (auto element : in_data.as_process()) {
				return_value += string_representation(element);
				return_value += " ";
			}
			return_value += "]";
		}
		return return_value;
	}

	data make_number(long double num) {
		return data(data_type::number, num);
	}

	data make_string(std::string str) {
		return data(data_type::string, str);
	}

	data make_symbol(std::string str) {
		return data(data_type::symbol, str);
	}

	data make_keyword(std::string str) {
		return data(data_type::keyword, str);
	}

	data make_boolean(bool b) {
		return data(data_type::boolean, b);
	}

	data make_tuple(std::vector<data> tuple) {
		return data(data_type::tuple, tuple);
	}

	data make_process(std::vector<data> proc) {
		return data(data_type::process, proc);
	}

	extern data make_map(std::map<data, data> map) {
		return data(data_type::map, map);
	}

	extern data make_container(enviroment container) {
		return data(data_type::container, container);
	}

	extern data make_container() {
		return data(data_type::container, enviroment(env_type::container));
	}

}
