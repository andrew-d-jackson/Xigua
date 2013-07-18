#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <limits>

#include "datatype.hpp"
#include "enviroment.hpp"

namespace Xigua
{
	namespace Functions
	{

		DataType func_less_than(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			DataType return_data(DataTypes::Bool);
			return_data.boolean = true;

			long double previous_num = std::numeric_limits<long double>::min();

			for (const auto & input : inputs)
			{
				if (input.type != DataTypes::Number)
				{
					std::cout << "Not a Number";
					exit(1);
				}
				
				if (previous_num < input.number)
				{
					previous_num = input.number;
				}
				else
				{
					return_data.boolean = false;
				}
			}

			return return_data;
		}

		DataType func_greater_than(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			DataType return_data(DataTypes::Bool);
			return_data.boolean = true;

			long double previous_num = std::numeric_limits<long double>::max();

			for (const auto & input : inputs)
			{
				if (input.type != DataTypes::Number)
				{
					std::cout << "Not a Number";
					exit(1);
				}

				if (previous_num > input.number)
				{
					previous_num = input.number;
				}
				else
				{
					return_data.boolean = false;
				}
			}

			return return_data;
		}

		DataType func_equals(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			DataType return_data(DataTypes::Bool);
			return_data.boolean = true;

			long double previous_num = inputs.at(0).number;

			for (const auto & input : inputs)
			{
				if (input.type != DataTypes::Number)
				{
					std::cout << "Not a Number";
					exit(1);
				}

				if (input.number == previous_num)
				{
					previous_num = input.number;
				}
				else
				{
					return_data.boolean = false;
				}
			}

			return return_data;
		}

		DataType func_add(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			DataType return_data(DataTypes::Number);
			return_data.number = 0;

			for (const auto & input : inputs)
			{
				if (input.type != DataTypes::Number)
				{
					std::cout << "Not a Number";
					exit(1);
				}
				return_data.number = return_data.number + input.number;
			}

			return return_data;
		}

		DataType func_minus(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			DataType return_data(DataTypes::Number);
			return_data.number = inputs.at(0).number * 2;

			for (const auto & input : inputs)
			{
				if (input.type != DataTypes::Number)
				{
					std::cout << "Not a Number";
					exit(1);
				}
				return_data.number = return_data.number - input.number;
			}

			return return_data;
		}

		DataType func_multiply(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			DataType return_data(DataTypes::Number);
			return_data.number = inputs.at(0).number * inputs.at(1).number;
			return return_data;
		}

		DataType func_divide(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			DataType return_data(DataTypes::Number);
			return_data.number = inputs.at(0).number / inputs.at(1).number;
			return return_data;
		}

		DataType func_concatinate_strings(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			DataType return_data(DataTypes::String);
			return_data.string = inputs.at(0).string + inputs.at(1).string;
			return return_data;
		}

		DataType func_uppercase_string(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			DataType return_data(DataTypes::String);
			return_data.string = inputs.at(0).string;
			return return_data;
		}

		DataType func_print_line(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			if (inputs.at(0).type == DataTypes::String)
				std::cout << inputs.at(0).string << std::endl;
			else if (inputs.at(0).type == DataTypes::Number)
				std::cout << inputs.at(0).number << std::endl;
			else if (inputs.at(0).type == DataTypes::Bool)
				if (inputs.at(0).boolean)
					std::cout << "true" << std::endl;
				else
					std::cout << "false" << std::endl;


			return DataType(DataTypes::None);
		}

		DataType func_if(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			if (inputs.at(0).evaluate(enviroment).boolean)
				return inputs.at(1).evaluate(enviroment);
			else
				return inputs.at(2).evaluate(enviroment);
		}

		DataType func_define(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			enviroment->set(inputs.at(0).string, inputs.at(1).evaluate(enviroment));
			return DataType(DataTypes::None);
		}

		DataType func_get_input(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			std::string i;
			std::cin >> i;

			DataType return_data(DataTypes::String);
			return_data.string = i;
			return return_data;
		}

		DataType func_lambda(std::vector<DataType> inputs, Enviroment* enviroment)
		{
			Enviroment nenv(enviroment);
			DataType return_data(DataTypes::Function);

			xigua_lambda_t fn = [nenv, inputs](std::vector<DataType> fn_inputs, Enviroment* fn_enviroment)mutable->DataType
			{
				for (unsigned int i(0); i < fn_inputs.size(); i++)
				{
					nenv.set(inputs.at(0).list.at(i).string, fn_inputs.at(i));
				}

				return inputs.at(1).evaluate(&nenv);
			};

			return_data.set_function(fn, inputs.at(0).list.size(), 0, true);

			return return_data;
		}

	}


	Enviroment get_global_enviroment()
	{
		Enviroment enviroment;

		enviroment.defined_variables["+"] = DataType(DataTypes::Function);
		enviroment.defined_variables["+"].set_function(&Functions::func_add, 2, 0, true);

		enviroment.defined_variables["-"] = DataType(DataTypes::Function);
		enviroment.defined_variables["-"].set_function(&Functions::func_minus, 2, 0, true);

		enviroment.defined_variables["*"] = DataType(DataTypes::Function);
		enviroment.defined_variables["*"].set_function(&Functions::func_multiply, 2, 0, true);
		
		enviroment.defined_variables["/"] = DataType(DataTypes::Function);
		enviroment.defined_variables["/"].set_function(&Functions::func_divide, 2, 0, true);

		enviroment.defined_variables["<"] = DataType(DataTypes::Function);
		enviroment.defined_variables["<"].set_function(&Functions::func_less_than, 2, 0, true);

		enviroment.defined_variables[">"] = DataType(DataTypes::Function);
		enviroment.defined_variables[">"].set_function(&Functions::func_greater_than, 2, 0, true);
		
		enviroment.defined_variables["=="] = DataType(DataTypes::Function);
		enviroment.defined_variables["=="].set_function(&Functions::func_equals, 2, 0, true);

		enviroment.defined_variables["conc"] = DataType(DataTypes::Function);
		enviroment.defined_variables["conc"].set_function(&Functions::func_concatinate_strings, 2, 0, true);

		enviroment.defined_variables["println"] = DataType(DataTypes::Function);
		enviroment.defined_variables["println"].set_function(&Functions::func_print_line, 1, 0, true);

		enviroment.defined_variables["if"] = DataType(DataTypes::Function);
		enviroment.defined_variables["if"].set_function(&Functions::func_if, 3, 0, false);

		enviroment.defined_variables["="] = DataType(DataTypes::Function);
		enviroment.defined_variables["="].set_function(&Functions::func_define, 2, 0, false);

		enviroment.defined_variables["fn"] = DataType(DataTypes::Function);
		enviroment.defined_variables["fn"].set_function(&Functions::func_lambda, 2, 0, false);

		enviroment.defined_variables["get-input"] = DataType(DataTypes::Function);
		enviroment.defined_variables["get-input"].set_function(&Functions::func_get_input, 0, 0, true);

		return enviroment;
	}
}
