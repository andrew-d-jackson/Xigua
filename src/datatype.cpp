#include "datatype.hpp"

namespace Xigua
{

	DataType::DataType(DataTypes data_type)
	{
		d_type = data_type;
	}

	DataType::DataType(DataTypes data_type, std::string string_data)
	{
		d_type = data_type;
		d_string = string_data;
	}

	DataType::DataType(DataTypes data_type, long double number_data)
	{
		d_type = data_type;
		d_number = number_data;
	}

	DataType::DataType(DataTypes data_type, bool boolean_data)
	{
		d_type = data_type;
		d_boolean = boolean_data;
	}

	DataType::DataType(DataTypes data_type, std::vector<DataType> list_data)
	{
		d_type = data_type;
		d_list = list_data;
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

	std::vector<DataType> DataType::proc() const
	{
		return d_list;
	}

	void DataType::proc(std::vector<DataType> proc)
	{
		d_list = proc;
	}

	void DataType::proc_push_back(DataType item)
	{
		d_list.push_back(item);
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
				if (it->first.first == args.size())
					function_to_call = it;
			}
		}

		if (function_to_call == d_func_map.end())
		{
			int current_biggest_args_with_repeating = 0;
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

			if (current_biggest_args_with_repeating == 0)
			{
				std::cout << "Wrong amount of args passed to function";
				exit(1);
			}
			else
			{
				int args_size = function_to_call->first.first;
				DataType repeating_data(DataTypes::Tuple);

				for (int i(args_size); i < args.size(); i++)
					repeating_data.proc_push_back(args.at(i));

				for (int i(args_size); i < args.size(); i++)
					args.pop_back();

				args.push_back(repeating_data);
			}

		}

		if (std::get<1>(function_to_call->second)) //should evaluate
		{
			for (auto & item : args)
			{
				if (item.d_type == DataTypes::Proc || item.d_type == DataTypes::Symbol)
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
			if (d_list.size() == 0)
			{
				return DataType(DataTypes::None);
			}
			else if (d_list.at(0).d_type == DataTypes::Symbol)
			{
				auto firstElement = d_list.begin() + 1;
				auto lastElement = d_list.end();
				std::vector<DataType> functionArgs(firstElement, lastElement);

				return d_list.at(0).evaluate(enviroment).call_function(functionArgs, enviroment);
			}
			else
			{
				for (DataType item : d_list)
					item.evaluate(enviroment);
			}
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
