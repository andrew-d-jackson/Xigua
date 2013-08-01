#pragma once

#include <vector>
#include <functional>
#include <limits>

#include "../datatype.hpp"
#include "../enviroment.hpp"
#include "../functionutils.hpp"


namespace Xigua
{
	namespace Functions
	{
		namespace Math
		{

			DataType less_than(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 2);
				Xigua::FunctionUtils::assert_all_types_are("less than", arguments, DataTypes::Number);

				long double previous_number = arguments.at(0).number();
				for (int i(1); i < arguments.size(); i++)
				{
					if (previous_number < arguments.at(i).number()){
						previous_number = arguments.at(i).number();
					} else {
						return DataType(DataTypes::Bool, false); 
					}
				}

				return DataType(DataTypes::Bool, true);
			}

			DataType greater_than(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 2);
				Xigua::FunctionUtils::assert_all_types_are("greater than", arguments, DataTypes::Number);

				long double previous_number = arguments.at(0).number();
				for (int i(1); i < arguments.size(); i++)
				{
					if (previous_number > arguments.at(i).number()){
						previous_number = arguments.at(i).number();
					} else {
						return DataType(DataTypes::Bool, false); 
					}
				}

				return DataType(DataTypes::Bool, true);
			}

			DataType equal_to(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 2);

				for (int i(1); i < arguments.size(); i++)
				{
					if (arguments.at(0) != arguments.at(i)){
						return DataType(DataTypes::Bool, false); 
					}
				}

				return DataType(DataTypes::Bool, true);
			}

			DataType add(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 2);
				Xigua::FunctionUtils::assert_all_types_are("add", arguments, DataTypes::Number);

				long double return_value = arguments.at(0).number();
				for (int i(1); i < arguments.size(); i++)
				{
					return_value += arguments.at(i).number();
				}

				return DataType(DataTypes::Number, return_value);
			}

			DataType minus(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 2);
				Xigua::FunctionUtils::assert_all_types_are("minus", arguments, DataTypes::Number);

				long double return_value = arguments.at(0).number();
				for (int i(1); i < arguments.size(); i++)
				{
					return_value -= arguments.at(i).number();
				}

				return DataType(DataTypes::Number, return_value);
			}

			DataType multiply(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 2);
				Xigua::FunctionUtils::assert_all_types_are("multiply", arguments, DataTypes::Number);

				long double return_value = arguments.at(0).number();
				for (int i(1); i < arguments.size(); i++)
				{
					return_value *= arguments.at(i).number();
				}

				return DataType(DataTypes::Number, return_value);
			}

			DataType divide(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 2);
				Xigua::FunctionUtils::assert_all_types_are("divide", arguments, DataTypes::Number);

				long double return_value = arguments.at(0).number();
				for (int i(1); i < arguments.size(); i++)
				{
					return_value /= arguments.at(i).number();
				}

				return DataType(DataTypes::Number, return_value);
			}

		}
	}
}