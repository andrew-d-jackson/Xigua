#pragma once

#include <vector>
#include <string>
#include <functional>
#include <limits>

#include "../datatype.hpp"
#include "../enviroment.hpp"


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

				for (auto item : inputs)
				{
					if (item.type() != DataTypes::Symbol) {
						std::cout << "non-symbol passed as function argument name";
						exit(1);
					} else if (item.symbol() == "&") {
						repeating = 1;
					}
				}

				xigua_lambda_t fn = [nenv, inputs](std::vector<DataType> fn_inputs, Enviroment* fn_enviroment)mutable->DataType
				{
					for (unsigned int i(0); i < fn_inputs.size(); i++)
					{
						if (inputs.at(i).symbol() != "&")
							nenv.set(inputs.at(0).tuple().at(i).string(), fn_inputs.at(i));
					}

					return inputs.at(1).evaluate(&nenv);
				};

				return_data.set_function(fn, inputs.at(0).tuple().size(), repeating, true);

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
				if (inputs.at(0).type() == DataTypes::String)
					std::cout << inputs.at(0).string() << std::endl;
				else if (inputs.at(0).type() == DataTypes::Number)
					std::cout << inputs.at(0).number() << std::endl;
				else if (inputs.at(0).type() == DataTypes::Bool)
					if (inputs.at(0).boolean()) {
						std::cout << "true" << std::endl;
					} else {
						std::cout << "false" << std::endl;
					}
				else if (inputs.at(0).type() == DataTypes::Tuple)
					std::cout << "<Tuple Size: " << inputs.at(0).tuple().size() << ">" << std::endl;
				else if (inputs.at(0).type() == DataTypes::Function)
					std::cout << "<Function>" << std::endl;

				return DataType(DataTypes::None);
			}

			DataType get_input(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				std::string str;
				std::cin >> str;
				return DataType(DataTypes::String, str);
			}

		}
	}
}