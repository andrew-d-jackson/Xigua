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
		namespace Tuple
		{

			DataType join(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 2);

				std::vector<DataType> return_value;
				for (auto argument : arguments)
				{
					if (argument.type() == DataTypes::Tuple) {
						for (auto element : argument.tuple())
							return_value.push_back(element);
					} else {
						return_value.push_back(argument);
					}
				}

				return DataType(DataTypes::Tuple, return_value);
			}

			DataType at(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Number || inputs.at(1).type() != DataTypes::Tuple)
					Xigua::FunctionUtils::wrong_type_error("at");

				if (inputs.at(0).number() < 0  || inputs.at(0).number() > inputs.at(1).tuple().size() - 1)
					Xigua::FunctionUtils::misc_error("at", "not in rage of tuple");

				return inputs.at(1).tuple().at(inputs.at(0).number());
			}

			DataType size(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Tuple)
					Xigua::FunctionUtils::wrong_type_error("size");

				return DataType(DataTypes::Number, (long double)inputs.at(0).tuple().size());
			}

			DataType first(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Tuple)
					Xigua::FunctionUtils::wrong_type_error("first");

				if (inputs.at(0).tuple().size() < 1)
					Xigua::FunctionUtils::misc_error("first", "not in rage of tuple");

				return inputs.at(0).tuple().at(0);
			}

			DataType last(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Tuple)
					Xigua::FunctionUtils::wrong_type_error("last");

				if (inputs.at(0).tuple().size() < 1)
					Xigua::FunctionUtils::misc_error("last", "not in rage of tuple");

				return inputs.at(0).tuple().at(inputs.at(0).tuple().size()-1);
			}


		}
	}
}