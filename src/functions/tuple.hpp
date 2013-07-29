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

		}
	}
}