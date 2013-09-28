#include "datatype.hpp"

namespace Xigua
{

	DataType::DataType(DataTypes data_type)
	{
		type(data_type);
	}

	DataType::DataType(DataTypes data_type, std::string string_data)
	{
		type(data_type);
		if (data_type == DataTypes::String){
			string(string_data);
		} else if (data_type == DataTypes::Symbol){
			symbol(string_data);
		} else {
			std::cout << "Wrong Data Passed to DataType string_data" << std::endl;
			exit(1);
		}
	}

	DataType::DataType(DataTypes data_type, long double number_data)
	{
		type(data_type);
		if (data_type == DataTypes::Number){
			number(number_data);
		} else {
			std::cout << "Wrong Data Passed to DataType number_data" << std::endl;
			exit(1);
		}
	}

	DataType::DataType(DataTypes data_type, bool boolean_data)
	{
		type(data_type);
		if (data_type == DataTypes::Bool){
			boolean(boolean_data);
		} else {
			std::cout << "Wrong Data Passed to DataType boolean_data" << std::endl;
			exit(1);
		}
	}

	DataType::DataType(DataTypes data_type, std::vector<DataType> list_data)
	{
		type(data_type);
		if (data_type == DataTypes::Tuple){
			tuple(list_data);
		} else if (data_type == DataTypes::Proc){
			proc(list_data);
		} else if (data_type == DataTypes::HashMap) {
			hash_map(list_data);
		} else {
			std::cout << "Wrong Data Passed to DataType list_data";
			exit(1);
		}
	}

	DataType::DataType(DataTypes data_type, std::map<DataType, DataType> map_data)
	{
		type(data_type);
		if (data_type == DataTypes::HashMap){
			hash_map(map_data);
		}  else {
			std::cout << "Wrong Data Passed to DataType map_data";
			exit(1);
		}
		
	}

	bool DataType::operator==(const DataType & other) const
	{
		if (type() != other.type())
			return false;

		if (type() == DataTypes::None)
			return true;

		if (type() == DataTypes::Symbol)
			return false;
		
		if (type() == DataTypes::Bool)
			return (boolean() == other.boolean());

		if (type() == DataTypes::String)
			return (string() == other.string());

		if (type() == DataTypes::Number)
			return (number() == other.number());

		if (type() == DataTypes::Tuple)
			return (tuple() == other.tuple());

		if (type() == DataTypes::Proc)
			return false;

		if (type() == DataTypes::Function)
			return false;

		return false;
	}

	bool DataType::operator!=(const DataType & other) const
	{
		return !(*this == other);
	}

	bool DataType::operator<(const DataType & other) const
	{
		if (type() != other.type())
			return (type() < other.type());

		if (type() == DataTypes::None)
			return false;

		if (type() == DataTypes::Symbol)
			return (symbol() < other.symbol());
		
		if (type() == DataTypes::Bool)
			return (boolean() < other.boolean());

		if (type() == DataTypes::String)
			return (string() < other.string());

		if (type() == DataTypes::Number)
			return (number() < other.number());

		if (type() == DataTypes::Tuple)
			return (tuple() < other.tuple());

		if (type() == DataTypes::Proc)
			return false;

		if (type() == DataTypes::Function)
			return false;

		return false;
	}


	DataTypes DataType::type() const
	{
		return d_type;
	}

	void DataType::type(DataTypes in_type)
	{
		d_type = in_type;

		if (in_type == DataTypes::None){
			data_pointer = nullptr;
		} else if (in_type == DataTypes::Symbol){
			data_pointer = std::shared_ptr<void>(new std::string());
		} else if (in_type == DataTypes::Bool){
			data_pointer = std::shared_ptr<void>(new bool(false));
		} else if (in_type == DataTypes::String){
			data_pointer = std::shared_ptr<void>(new std::string());
		} else if (in_type == DataTypes::Number){
			data_pointer = std::shared_ptr<void>(new long double(0));
		} else if (in_type == DataTypes::Tuple){
			data_pointer = std::shared_ptr<void>(new std::vector<DataType>());
		} else if (in_type == DataTypes::HashMap){
			data_pointer = std::shared_ptr<void>(new std::map<DataType, DataType>());
		} else if (in_type == DataTypes::Proc){
			data_pointer = std::shared_ptr<void>(new std::vector<DataType>());
		} else if (in_type == DataTypes::Function){
			data_pointer = std::shared_ptr<void>(new function_map_t());
		} else {
			std::cout << "Something Wrong Passes To Type" << std::endl;
			exit(1);
		}
	}

	std::string DataType::string() const
	{
	//	return d_string;
		return *(static_cast<std::string*>(data_pointer.get()));
	}

	void DataType::string(std::string in_string)
	{
	//	d_string = in_string;
		data_pointer = std::shared_ptr<void>(new std::string(in_string));
	}

	std::string DataType::as_string() const
	{
		std::string return_value = "";
		if (type() == DataTypes::String) {
			return_value += string();
		} else if (type() == DataTypes::Bool){
			if (boolean()) {
				return_value += "true";
			} else {
				return_value += "false";
			}
		} else if (type() == DataTypes::Number){
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
		} else if (type() == DataTypes::Tuple){
			return_value += "{ ";
			for (auto element : tuple()) {
				return_value += element.as_string();
				return_value += " ";
			}
			return_value += "}";
		} else if (type() == DataTypes::HashMap){
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


	std::string DataType::symbol() const
	{
		return *(static_cast<std::string*>(data_pointer.get()));
	}
	
	void DataType::symbol(std::string symbol_name)
	{
		data_pointer = std::shared_ptr<void>(new std::string(symbol_name));
	}

	long double DataType::number() const
	{
		return *(static_cast<long double*>(data_pointer.get()));
	}

	void DataType::number(long double in_number)
	{
		data_pointer = std::shared_ptr<void>(new long double(in_number));
	}

	std::vector<DataType> DataType::tuple() const
	{
		return *(static_cast<std::vector<DataType>*>(data_pointer.get()));
	}

	void DataType::tuple(std::vector<DataType> tuple)
	{
		data_pointer = std::shared_ptr<void>(new std::vector<DataType>(tuple));
	}

	std::map<DataType, DataType> DataType::hash_map() const
	{
		return *(static_cast<std::map<DataType, DataType>*>(data_pointer.get()));
	}
	
	void DataType::hash_map(std::map<DataType, DataType> in_map)
	{
		data_pointer = std::shared_ptr<void>(new std::map<DataType, DataType>(in_map));
	}

	void DataType::hash_map(std::vector<DataType> in_list)
	{
		std::map<DataType, DataType> temp_map;
		for (unsigned int i(0); i + 1 < in_list.size(); i += 2)
		{
			temp_map[in_list.at(i)] = in_list.at(i + 1);
		}
		hash_map(temp_map);
	}

	std::vector<DataType> DataType::proc() const
	{
		return *(static_cast<std::vector<DataType>*>(data_pointer.get()));
	}

	void DataType::proc(std::vector<DataType> proc)
	{
		data_pointer = std::shared_ptr<void>(new std::vector<DataType>(proc));
	}

	bool DataType::boolean() const
	{
		return *(static_cast<bool*>(data_pointer.get()));
	}

	void DataType::boolean(bool in_boolean)
	{
		data_pointer = std::shared_ptr<void>(new bool(in_boolean));
	}

	DataType::function_map_t DataType::function_map() const
	{
		return *(static_cast<function_map_t*>(data_pointer.get()));
	}

	void DataType::function_map(function_map_t in_fmap)
	{
		data_pointer = std::shared_ptr<void>(new function_map_t(in_fmap));
	}


	void DataType::set_function(xigua_lambda_t func, int num_args, int repeating_args, bool should_eval)
	{
		auto function_map_copy = function_map();
		function_map_copy[std::make_pair(num_args, repeating_args)] = std::make_tuple(func, should_eval);
		function_map(function_map_copy);
	}

	DataType DataType::call_function(std::vector<DataType> & args, Enviroment * enviroment, std::vector<std::string> function_call_list)
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
						args.push_back(DataType(DataTypes::Tuple));
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
				std::vector<DataType> repeating_data; 

				for (int i(args_size); i < prev_args_size; i++)
					repeating_data.push_back(args.at(i));

				for (int i(args_size); i < prev_args_size; i++)
					args.pop_back();

				args.push_back(DataType(DataTypes::Tuple, repeating_data));
			}

		}

		if (std::get<1>(function_to_call->second)) //should evaluate
		{
			for (auto & item : args)
			{
				if (item.type() == DataTypes::Proc || item.type() == DataTypes::Symbol || item.type() == DataTypes::Tuple)
					item = item.evaluate(enviroment, function_call_list);

			}
		}

		return std::get<0>(function_to_call->second)(args, enviroment, function_call_list);
	}

	DataType DataType::evaluate(Enviroment * enviroment, std::vector<std::string> function_call_list)
	{
		if (type() == DataTypes::Symbol)
		{
			DataType* symbol_value = enviroment->find(symbol());
			if (symbol_value == nullptr)
			{
				throw Xigua::Error(Xigua::ErrorTypes::INVALID_ARGS, "Cannot Find Symbol", function_call_list);
			}
			return *symbol_value;
		}
		else if (type() == DataTypes::Number)
		{
			return *this;
		}
		else if (type() == DataTypes::Function)
		{
			return *this;
		}
		else if (type() == DataTypes::String)
		{
			return *this;
		}
		else if (type() == DataTypes::Bool)
		{
			return *this;
		}
		else if (type() == DataTypes::Proc)
		{
			if (proc().at(0).type() == DataTypes::Proc || proc().at(0).type() == DataTypes::Symbol)
			{
				if (proc().at(0).type() == DataTypes::Symbol)
				{
					function_call_list.push_back(proc().at(0).symbol());
				}

				std::vector<DataType> new_proc_data = proc();
				new_proc_data.at(0) = proc().at(0).evaluate(enviroment, function_call_list);
				proc(new_proc_data);
			}

			if (proc().size() == 0)
			{
				return DataType(DataTypes::None);
			}
			else if (proc().at(0).type() == DataTypes::Function)
			{
				auto process_copy = proc();
				auto firstElement = process_copy.begin() + 1;
				auto lastElement = process_copy.end();
				std::vector<DataType> functionArgs(firstElement, lastElement);

				return proc().at(0).call_function(functionArgs, enviroment, function_call_list);
			}
			else
			{
				DataType return_value = DataType(DataTypes::None);
				for (DataType item : proc())
					return_value = item.evaluate(enviroment, function_call_list);
				return return_value;
			}
		}
		else if (type() == DataTypes::Tuple)
		{
			std::vector<DataType> new_tuple_data;
			for (auto data : tuple())
			{
				new_tuple_data.push_back(data.evaluate(enviroment, function_call_list));
			}
			return DataType(DataTypes::Tuple, new_tuple_data);
		}
		else if (type() == DataTypes::HashMap)
		{
			std::map<DataType, DataType> new_tuple_data;
			for (auto data : hash_map())
			{
				auto first = data.first;
				auto second = data.second;
				new_tuple_data[first.evaluate(enviroment, function_call_list)] = second.evaluate(enviroment, function_call_list);
			}
			return DataType(DataTypes::HashMap, new_tuple_data);
		}

		return DataType(DataTypes::None);
	}

	void DataType::print(int indentation)
	{
		if (type() == DataTypes::Proc)
		{
			std::cout << "p";
			for (auto i : proc())
				i.print(indentation + 1);
			std::cout << std::endl;
		}
		else if (type() == DataTypes::Tuple)
		{
			std::cout << "t";
			for (auto i : tuple())
				i.print(indentation + 1);
			std::cout << std::endl;
		}
		else if (type() == DataTypes::Symbol)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "Symbol: " << symbol() << std::endl;
		}
		else if (type() == DataTypes::String)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "String: " << string() << std::endl;
		}
		else if (type() == DataTypes::Number)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "Number: " << number() << std::endl;
		}
		else if (type() == DataTypes::Bool)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "Boolean: " << boolean() << std::endl;
		}
	}

}
