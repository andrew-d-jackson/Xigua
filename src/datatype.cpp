#include "datatype.hpp"

namespace xig
{

	data::data(data_type in_type)
	{
		type(in_type);
	}

	data::data(data_type in_type, std::string string_data)
	{
		type(in_type);
		if (in_type == data_type::String){
			string(string_data);
		} else if (in_type == data_type::Symbol){
			symbol(string_data);
		} else {
			std::cout << "Wrong Data Passed to data string_data" << std::endl;
			exit(1);
		}
	}

	data::data(data_type in_type, long double number_data)
	{
		type(in_type);
		if (in_type == data_type::Number){
			number(number_data);
		} else {
			std::cout << "Wrong Data Passed to data number_data" << std::endl;
			exit(1);
		}
	}

	data::data(data_type in_type, bool boolean_data)
	{
		type(in_type);
		if (in_type == data_type::Bool){
			boolean(boolean_data);
		} else {
			std::cout << "Wrong Data Passed to data boolean_data" << std::endl;
			exit(1);
		}
	}

	data::data(data_type in_type, std::vector<data> list_data)
	{
		type(in_type);
		if (in_type == data_type::Tuple){
			tuple(list_data);
		} else if (in_type == data_type::Proc){
			proc(list_data);
		} else if (in_type == data_type::HashMap) {
			hash_map(list_data);
		} else {
			std::cout << "Wrong Data Passed to data list_data";
			exit(1);
		}
	}

	data::data(data_type in_type, std::map<data, data> map_data)
	{
		type(in_type);
		if (in_type == data_type::HashMap){
			hash_map(map_data);
		}  else {
			std::cout << "Wrong Data Passed to data map_data";
			exit(1);
		}
		
	}

	bool data::operator==(const data & other) const
	{
		if (type() != other.type())
			return false;

		if (type() == data_type::None)
			return true;

		if (type() == data_type::Symbol)
			return false;
		
		if (type() == data_type::Bool)
			return (boolean() == other.boolean());

		if (type() == data_type::String)
			return (string() == other.string());

		if (type() == data_type::Number)
			return (number() == other.number());

		if (type() == data_type::Tuple)
			return (tuple() == other.tuple());

		if (type() == data_type::Proc)
			return false;

		if (type() == data_type::Function)
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

		if (type() == data_type::None)
			return false;

		if (type() == data_type::Symbol)
			return (symbol() < other.symbol());
		
		if (type() == data_type::Bool)
			return (boolean() < other.boolean());

		if (type() == data_type::String)
			return (string() < other.string());

		if (type() == data_type::Number)
			return (number() < other.number());

		if (type() == data_type::Tuple)
			return (tuple() < other.tuple());

		if (type() == data_type::Proc)
			return false;

		if (type() == data_type::Function)
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

		if (in_type == data_type::None){
			data_pointer = nullptr;
		} else if (in_type == data_type::Symbol){
			data_pointer = std::shared_ptr<void>(new std::string());
		} else if (in_type == data_type::Bool){
			data_pointer = std::shared_ptr<void>(new bool(false));
		} else if (in_type == data_type::String){
			data_pointer = std::shared_ptr<void>(new std::string());
		} else if (in_type == data_type::Number){
			data_pointer = std::shared_ptr<void>(new long double(0));
		} else if (in_type == data_type::Tuple){
			data_pointer = std::shared_ptr<void>(new std::vector<data>());
		} else if (in_type == data_type::HashMap){
			data_pointer = std::shared_ptr<void>(new std::map<data, data>());
		} else if (in_type == data_type::Proc){
			data_pointer = std::shared_ptr<void>(new std::vector<data>());
		} else if (in_type == data_type::Function){
			data_pointer = std::shared_ptr<void>(new function_map_t());
		} else {
			std::cout << "Something Wrong Passes To Type" << std::endl;
			exit(1);
		}
	}

	std::string data::string() const
	{
	//	return d_string;
		return *(static_cast<std::string*>(data_pointer.get()));
	}

	void data::string(std::string in_string)
	{
	//	d_string = in_string;
		data_pointer = std::shared_ptr<void>(new std::string(in_string));
	}

	std::string data::as_string() const
	{
		std::string return_value = "";
		if (type() == data_type::String) {
			return_value += string();
		} else if (type() == data_type::Bool){
			if (boolean()) {
				return_value += "true";
			} else {
				return_value += "false";
			}
		} else if (type() == data_type::Number){
			std::stringstream ss;
			ss << std::fixed;
			ss << number();
			std::string str = ss.str();
			int s;
		    for (s = str.length()-1; s > 0; s--) {
		        if(str[s] == '0')
		        	str.erase(s,1);
		        else
		        	break;
		    }
		    if (str[s] == '.')
		    	str.erase(s,1);
		    return_value += str;
		} else if (type() == data_type::Tuple){
			return_value += "{ ";
			for (auto element : tuple()) {
				return_value += element.as_string();
				return_value += " ";
			}
			return_value += "}";
		} else if (type() == data_type::HashMap){
			return_value += "#{ ";
			for (auto & element : hash_map()) {
				return_value += element.first.as_string();
				return_value += " => ";
				return_value += element.second.as_string();
				return_value += ", ";
			}
			return_value += "}";
		}
		return return_value;
	}


	std::string data::symbol() const
	{
		return *(static_cast<std::string*>(data_pointer.get()));
	}
	
	void data::symbol(std::string symbol_name)
	{
		data_pointer = std::shared_ptr<void>(new std::string(symbol_name));
	}

	long double data::number() const
	{
		return *(static_cast<long double*>(data_pointer.get()));
	}

	void data::number(long double in_number)
	{
		data_pointer = std::shared_ptr<void>(new long double(in_number));
	}

	std::vector<data> data::tuple() const
	{
		return *(static_cast<std::vector<data>*>(data_pointer.get()));
	}

	void data::tuple(std::vector<data> tuple)
	{
		data_pointer = std::shared_ptr<void>(new std::vector<data>(tuple));
	}

	std::map<data, data> data::hash_map() const
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

	std::vector<data> data::proc() const
	{
		return *(static_cast<std::vector<data>*>(data_pointer.get()));
	}

	void data::proc(std::vector<data> proc)
	{
		data_pointer = std::shared_ptr<void>(new std::vector<data>(proc));
	}

	bool data::boolean() const
	{
		return *(static_cast<bool*>(data_pointer.get()));
	}

	void data::boolean(bool in_boolean)
	{
		data_pointer = std::shared_ptr<void>(new bool(in_boolean));
	}

	data::function_map_t data::function_map() const
	{
		return *(static_cast<function_map_t*>(data_pointer.get()));
	}

	void data::function_map(function_map_t in_fmap)
	{
		data_pointer = std::shared_ptr<void>(new function_map_t(in_fmap));
	}


	void data::set_function(xigua_lambda_t func, int num_args, int repeating_args, bool should_eval)
	{
		auto function_map_copy = function_map();
		function_map_copy[std::make_pair(num_args, repeating_args)] = std::make_tuple(func, should_eval);
		function_map(function_map_copy);
	}

	data data::call_function(std::vector<data> & args, Enviroment * enviroment, std::vector<std::string> function_call_list)
	{
		auto function_map_copy = function_map();
		auto function_to_call = function_map_copy.find(std::make_pair(args.size(), 0));

		if (function_to_call == function_map_copy.end())
		{
			for (auto it = function_map_copy.begin(); it != function_map_copy.end(); it++)
			{
				if (it->first.first == args.size()){
					function_to_call = it;
					for (int i(0); i < it->first.second; i++)
						args.push_back(data(data_type::Tuple));
				}
			}
		}

		if (function_to_call == function_map_copy.end())
		{
			int current_biggest_args_with_repeating = -1;
			int current_args_limit = args.size() - 1;

			for (auto it = function_map_copy.begin(); it != function_map_copy.end(); it++)
			{
				if (it->first.second > 0)
				{
					if (it->first.first <= current_args_limit && it->first.first > current_biggest_args_with_repeating)
					{
						current_biggest_args_with_repeating = it->first.first;
						function_to_call = it;
					}
				}
			}

			if (current_biggest_args_with_repeating == -1)
			{
				std::cout << "Wrong amount of args passed to function" << std::endl;
				std::cout << " args passed:" << args.size() << std::endl;
				for (auto i : args)
					i.print();

				exit(1);
			}
			else
			{
				int args_size = function_to_call->first.first;
				int prev_args_size = args.size();
				std::vector<data> repeating_data; 

				for (int i(args_size); i < prev_args_size; i++)
					repeating_data.push_back(args.at(i));

				for (int i(args_size); i < prev_args_size; i++)
					args.pop_back();

				args.push_back(data(data_type::Tuple, repeating_data));
			}

		}

		if (std::get<1>(function_to_call->second)) //should evaluate
		{
			for (auto & item : args)
			{
				if (item.type() == data_type::Proc || item.type() == data_type::Symbol || item.type() == data_type::Tuple)
					item = item.evaluate(enviroment, function_call_list);

			}
		}

		return std::get<0>(function_to_call->second)(args, enviroment, function_call_list);
	}

	data data::evaluate(Enviroment * enviroment, std::vector<std::string> function_call_list)
	{
		if (type() == data_type::Symbol)
		{
			data* symbol_value = enviroment->find(symbol());
			if (symbol_value == nullptr)
			{
				throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Cannot Find Symbol", function_call_list);
			}
			return *symbol_value;
		}
		else if (type() == data_type::Number)
		{
			return *this;
		}
		else if (type() == data_type::Function)
		{
			return *this;
		}
		else if (type() == data_type::String)
		{
			return *this;
		}
		else if (type() == data_type::Bool)
		{
			return *this;
		}
		else if (type() == data_type::Proc)
		{
			if (proc().at(0).type() == data_type::Proc || proc().at(0).type() == data_type::Symbol)
			{
				if (proc().at(0).type() == data_type::Symbol)
				{
					function_call_list.push_back(proc().at(0).symbol());
				}

				std::vector<data> new_proc_data = proc();
				new_proc_data.at(0) = proc().at(0).evaluate(enviroment, function_call_list);
				proc(new_proc_data);
			}

			if (proc().size() == 0)
			{
				return data(data_type::None);
			}
			else if (proc().at(0).type() == data_type::Function)
			{
				auto process_copy = proc();
				auto firstElement = process_copy.begin() + 1;
				auto lastElement = process_copy.end();
				std::vector<data> functionArgs(firstElement, lastElement);

				return proc().at(0).call_function(functionArgs, enviroment, function_call_list);
			}
			else
			{
				data return_value = data(data_type::None);
				for (data item : proc())
					return_value = item.evaluate(enviroment, function_call_list);
				return return_value;
			}
		}
		else if (type() == data_type::Tuple)
		{
			std::vector<data> new_tuple_data;
			for (auto data : tuple())
			{
				new_tuple_data.push_back(data.evaluate(enviroment, function_call_list));
			}
			return data(data_type::Tuple, new_tuple_data);
		}
		else if (type() == data_type::HashMap)
		{
			std::map<data, data> new_tuple_data;
			for (auto data : hash_map())
			{
				auto first = data.first;
				auto second = data.second;
				new_tuple_data[first.evaluate(enviroment, function_call_list)] = second.evaluate(enviroment, function_call_list);
			}
			return data(data_type::HashMap, new_tuple_data);
		}

		return data(data_type::None);
	}

	void data::print(int indentation)
	{
		if (type() == data_type::Proc)
		{
			std::cout << "p";
			for (auto i : proc())
				i.print(indentation + 1);
			std::cout << std::endl;
		}
		else if (type() == data_type::Tuple)
		{
			std::cout << "t";
			for (auto i : tuple())
				i.print(indentation + 1);
			std::cout << std::endl;
		}
		else if (type() == data_type::Symbol)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "Symbol: " << symbol() << std::endl;
		}
		else if (type() == data_type::String)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "String: " << string() << std::endl;
		}
		else if (type() == data_type::Number)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "Number: " << number() << std::endl;
		}
		else if (type() == data_type::Bool)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "Boolean: " << boolean() << std::endl;
		}
	}

}
