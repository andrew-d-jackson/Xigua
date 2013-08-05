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
		string(string_data);
	}

	DataType::DataType(DataTypes data_type, long double number_data)
	{
		type(data_type);
		number(number_data);
	}

	DataType::DataType(DataTypes data_type, bool boolean_data)
	{
		type(data_type);
		boolean(boolean_data);
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
			std::cout << "Not a valid list";
			exit(1);
		}
	}

	DataType::DataType(DataTypes data_type, std::map<DataType, DataType> map_data)
	{
		type(data_type);
		hash_map(map_data);
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
	}

	std::string DataType::string() const
	{
		return d_string;
	}

	void DataType::string(std::string in_string)
	{
		d_string = in_string;
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
		return d_string;
	}
	
	void DataType::symbol(std::string symbol_name)
	{
		d_string = symbol_name;
	}

	long double DataType::number() const
	{
		return d_number;
	}

	void DataType::number(long double in_number)
	{
		d_number = in_number;
	}

	std::vector<DataType> DataType::tuple() const
	{
		return d_list;
	}

	void DataType::tuple(std::vector<DataType> tuple)
	{
		d_list = tuple;
	}

	std::map<DataType, DataType> DataType::hash_map() const
	{
		return d_hashmap;
	}
	
	void DataType::hash_map(std::map<DataType, DataType> in_map)
	{
		d_hashmap = in_map;
	}

	void DataType::hash_map(std::vector<DataType> in_list)
	{
		for (int i(0); i+1 < in_list.size(); i+=2)
		{
			std::cout << in_list.at(i).as_string() << "=>" << in_list.at(i+1).as_string() << std::endl; 
			d_hashmap[in_list.at(i)] = in_list.at(i+1);
		}
	}

	std::vector<DataType> DataType::proc() const
	{
		return d_list;
	}

	void DataType::proc(std::vector<DataType> proc)
	{
		d_list = proc;
	}

	bool DataType::boolean() const
	{
		return d_boolean;
	}

	void DataType::boolean(bool in_boolean)
	{
		d_boolean = in_boolean;
	}

	DataType::function_map_t DataType::function_map() const
	{
		return d_func_map;
	}

	void DataType::function_map(function_map_t in_fmap)
	{
		d_func_map = in_fmap;
	}


	void DataType::set_function(xigua_lambda_t func, int num_args, int repeating_args, bool should_eval)
	{
		auto function_map_copy = function_map();
		function_map_copy[std::make_pair(num_args, repeating_args)] = std::make_tuple(func, should_eval);
		function_map(function_map_copy);
	}

	DataType DataType::call_function(std::vector<DataType> & args, Enviroment * enviroment)
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
					item = item.evaluate(enviroment);

			}
		}

		return std::get<0>(function_to_call->second)(args, enviroment);
	}

	DataType DataType::evaluate(Enviroment * enviroment)
	{
		if (type() == DataTypes::Symbol)
		{
			DataType* symbol_value = enviroment->find(symbol());
			if (symbol_value == nullptr)
			{
				std::cout << "Cannot Find Symbol: " << symbol() << std::endl;
				exit(1);
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
				std::vector<DataType> new_proc_data = proc();
				new_proc_data.at(0) = proc().at(0).evaluate(enviroment);
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

				return proc().at(0).call_function(functionArgs, enviroment);
			}
			else
			{
				DataType return_value = DataType(DataTypes::None);
				for (DataType item : proc())
					return_value = item.evaluate(enviroment);
				return return_value;
			}
		}
		else if (type() == DataTypes::Tuple)
		{
			std::vector<DataType> new_tuple_data;
			for (auto data : tuple())
			{
				new_tuple_data.push_back(data.evaluate(enviroment));
			}
			return DataType(DataTypes::Tuple, new_tuple_data);
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
