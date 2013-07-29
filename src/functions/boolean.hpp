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
		namespace Boolean
		{

			DataType boolean_not(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Bool)
					Xigua::FunctionUtils::wrong_type_error("boolean not");

				return DataType(DataTypes::Bool, !(inputs.at(0).boolean()));
			}

		}
	}
}