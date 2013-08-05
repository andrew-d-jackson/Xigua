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
			for (int i(0); i < list_data.size(); i+=2)
			{
				std::cout << list_data.at(i).as_string() << "=>" << list_data.at(i+1).as_string() << std::endl; 
				d_hashmap[list_data.at(i)] = list_data.at(i+1);
			}
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


	void DataType::set_function(xigua_lambda_t func, int num_args, int repeating_args, bool should_eval)
	{
		d_func_map[std::make_pair(num_args, repeating_args)] = std::make_tuple(func, should_eval);
	}

	DataType DataType::call_function(std::vector<DataType> & args, Enviroment * enviroment)
	{
		auto function_to_call = d_func_map.find(std::make_pair(args.size(), 0));

		if (function_to_call == d_func_map.end())
		{
			for (auto it = d_func_map.begin(); it != d_func_map.end(); it++)
			{
				if (it->first.first == args.size()){
					function_to_call = it;
					for (int i(0); i < it->first.second; i++)
						args.push_back(DataType(DataTypes::Tuple));
				}
			}
		}

		if (function_to_call == d_func_map.end())
		{
			int current_biggest_args_with_repeating = -1;
			int current_args_limit = args.size() - 1;

			for (auto it = d_func_map.begin(); it != d_func_map.end(); it++)
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
				if (item.d_type == DataTypes::Proc || item.d_type == DataTypes::Symbol || item.d_type == DataTypes::Tuple)
					item = item.evaluate(enviroment);

			}
		}

		return std::get<0>(function_to_call->second)(args, enviroment);
	}

	DataType DataType::evaluate(Enviroment * enviroment)
	{
		if (d_type == DataTypes::Symbol)
		{
			DataType* symbol_value = enviroment->find(d_string);
			if (symbol_value == nullptr)
			{
				std::cout << "Cannot Find Symbol: " << d_string << std::endl;
				exit(1);
			}
			return *symbol_value;
		}
		else if (d_type == DataTypes::Number)
		{
			return *this;
		}
		else if (d_type == DataTypes::Function)
		{
			return *this;
		}
		else if (d_type == DataTypes::String)
		{
			return *this;
		}
		else if (d_type == DataTypes::Bool)
		{
			return *this;
		}
		else if (d_type == DataTypes::Proc)
		{
			if (d_list.at(0).d_type == DataTypes::Proc || d_list.at(0).d_type == DataTypes::Symbol)
			{
				d_list.at(0) = d_list.at(0).evaluate(enviroment);
			}

			if (d_list.size() == 0)
			{
				return DataType(DataTypes::None);
			}
			else if (d_list.at(0).d_type == DataTypes::Function)
			{
				auto firstElement = d_list.begin() + 1;
				auto lastElement = d_list.end();
				std::vector<DataType> functionArgs(firstElement, lastElement);

				return d_list.at(0).call_function(functionArgs, enviroment);
			}
			else
			{
				DataType return_value = DataType(DataTypes::None);
				for (DataType item : d_list)
					return_value = item.evaluate(enviroment);
				return return_value;
			}
		}
		else if (d_type == DataTypes::Tuple)
		{
			std::vector<DataType> new_tuple_data;
			for (auto data : d_list)
			{
				new_tuple_data.push_back(data.evaluate(enviroment));
			}
			return DataType(DataTypes::Tuple, new_tuple_data);
		}

		return DataType(DataTypes::None);
	}

	void DataType::print(int indentation)
	{
		if (d_type == DataTypes::Proc)
		{
			std::cout << "p";
			for (auto i : d_list)
				i.print(indentation + 1);
			std::cout << std::endl;
		}
		else if (d_type == DataTypes::Tuple)
		{
			std::cout << "t";
			for (auto i : d_list)
				i.print(indentation + 1);
			std::cout << std::endl;
		}
		else if (d_type == DataTypes::Symbol)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "Symbol: " << d_string << std::endl;
		}
		else if (d_type == DataTypes::String)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "String: " << d_string << std::endl;
		}
		else if (d_type == DataTypes::Number)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "Number: " << d_number << std::endl;
		}
		else if (d_type == DataTypes::Bool)
		{
			for (int i(indentation); i > 0; i--)
				std::cout << "\t";
			std::cout << "Boolean: " << d_boolean << std::endl;
		}
	}

}
