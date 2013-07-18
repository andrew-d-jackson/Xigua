#include "datatype.hpp"

namespace Xigua
{

DataType::DataType(DataTypes data_type)
{
	type = data_type;
}

DataType::DataType(DataTypes data_type, std::string string_data)
{
	type = data_type;
	string = string_data;
}

DataType::DataType(DataTypes data_type, long double number_data)
{
	type = data_type;
	number = number_data;
}

DataType::DataType(DataTypes data_type, bool boolean_data)
{
	type = data_type;
	boolean = boolean_data;
}

void DataType::set_function(xigua_lambda_t func, int num_args, int repeating_args, bool should_eval)
{
	func_map[num_args] = std::make_tuple(func, repeating_args, should_eval);
}

DataType DataType::call_function(std::vector<DataType> & args, Enviroment * enviroment)
{
	auto finder = func_map.find(args.size());

	if (finder == func_map.end())
	{
		std::cout << "Wrong amount of args passed to function";
		exit(1);
	}

	if (std::get<2>(func_map[args.size()])) //should evaluate
	{
		for (auto & item : args)
		{
			if (item.type == DataTypes::Proc || item.type == DataTypes::Symbol)
				item = item.evaluate(enviroment);
		}
	}

	return std::get<0>(func_map[args.size()])(args, enviroment);
}

DataType DataType::evaluate(Enviroment * enviroment)
{
	if (type == DataTypes::Symbol)
	{
		DataType* symbol_value = enviroment->find(string);
		if (symbol_value == nullptr)
		{
			std::cout << "Cannot Find Symbol: " << string << std::endl;
			exit(1);
		}
		return *symbol_value;
	}
	else if (type == DataTypes::Number)
	{
		return *this;
	}
	else if (type == DataTypes::Function)
	{
		return *this;
	}
	else if (type == DataTypes::String)
	{
		return *this;
	}
	else if (type == DataTypes::Bool)
	{
		return *this;
	}
	else if (type == DataTypes::Proc)
	{
		if (list.size() == 0)
		{
			return DataType(DataTypes::None);
		}
		else if (list.at(0).type == DataTypes::Symbol)
		{
			auto firstElement = list.begin() + 1;
			auto lastElement = list.end();
			std::vector<DataType> functionArgs(firstElement, lastElement);

			return list.at(0).evaluate(enviroment).call_function(functionArgs, enviroment);
		}
		else
		{
			for (DataType item : list)
				item.evaluate(enviroment);
		}
	}

	return DataType(DataTypes::None);
}

void DataType::print(int indentation)
{
	if (type == DataTypes::Proc)
	{
		std::cout << "p";
		for (auto i : list)
			i.print(indentation + 1);
		std::cout << std::endl;
	}
	else if (type == DataTypes::Tuple)
	{
		std::cout << "t";
		for (auto i : list)
			i.print(indentation + 1);
		std::cout << std::endl;
	}
	else if (type == DataTypes::Symbol)
	{
		for (int i(indentation); i > 0; i--)
			std::cout << "\t";
		std::cout << "Symbol: " << string << std::endl;
	}
	else if (type == DataTypes::String)
	{
		for (int i(indentation); i > 0; i--)
			std::cout << "\t";
		std::cout << "String: " << string << std::endl;
	}
	else if (type == DataTypes::Number)
	{
		for (int i(indentation); i > 0; i--)
			std::cout << "\t";
		std::cout << "Number: " << number << std::endl;
	}
	else if (type == DataTypes::Bool)
	{
		for (int i(indentation); i > 0; i--)
			std::cout << "\t";
		std::cout << "Boolean: " << boolean << std::endl;
	}
}

}