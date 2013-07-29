#pragma once

#include <vector>
#include <string>
#include <functional>
#include <limits>

#include "../datatype.hpp"
#include "../enviroment.hpp"
#include "../functionutils.hpp"


namespace Xigua
{
	namespace Functions
	{
		namespace Core
		{

			DataType define(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				enviroment->set(inputs.at(0).string(), inputs.at(1).evaluate(enviroment));
				return DataType(DataTypes::None);
			}

			DataType create_lambda(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				Enviroment nenv(enviroment);
				DataType return_data(DataTypes::Function);

				int repeating = 0;

				for (auto item : inputs.at(0).tuple())
				{
					if (item.type() != DataTypes::Symbol) {
						std::cout << "non-symbol passed as function argument name" << std::endl;
						exit(1);
					} else if (item.symbol() == "&") {
						repeating = 1;
					}
				}

				xigua_lambda_t fn = [nenv, inputs](std::vector<DataType> fn_inputs, Enviroment* fn_enviroment)mutable->DataType
				{
					short missing = 0;
					for (unsigned int i(0); i < inputs.at(0).tuple().size(); ++i)
					{
						if (inputs.at(0).tuple().at(i).symbol() != "&") {
							nenv.set(inputs.at(0).tuple().at(i).symbol(), fn_inputs.at(i-missing));
						} else {
							missing = 1;
						}
					}

					return inputs.at(1).evaluate(&nenv);
				};

				return_data.set_function(fn, inputs.at(0).tuple().size()-(repeating*2), repeating, true);

				return return_data;
			}

			DataType if_expression(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).evaluate(enviroment).boolean())
					return inputs.at(1).evaluate(enviroment);
				else
					return inputs.at(2).evaluate(enviroment);
			}

			DataType print_line(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				std::cout << inputs.at(0).as_string() << std::endl;
				return DataType(DataTypes::None);
			}

			DataType get_input(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				std::string str;
				std::cin >> str;
				return DataType(DataTypes::String, str);
			}

		/*	DataType map(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 2);

				for (int i(0); i < arguments.at(1).tuple().size(); i++)
				{
					std::vector<DataType> temp_proc = { arguments.at(0) };
					for (int j(1); j < arguments.size(); j++)
						temp_proc.push_back(arguments.at(j).tuple().at(i))

					DataType temp_function(DataTypes::Proc, temp_proc);
					temp_function.evaluate();
				}

				return DataType(DataTypes::None);
			}
*/
			DataType apply(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Function || inputs.at(1).type() != DataTypes::Tuple)
					Xigua::FunctionUtils::wrong_type_error("apply");

				std::vector<DataType> temp_proc = { inputs.at(0) };

				for (auto data : inputs.at(1).tuple())
					temp_proc.push_back(data);

				DataType temp_function(DataTypes::Proc, temp_proc);
				return temp_function.evaluate(enviroment);
			}

		}
	}
}