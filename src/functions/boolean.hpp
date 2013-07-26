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
		namespace Boolean
		{

			DataType boolean_not(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				return DataType(DataTypes::Bool, !(inputs.at(0).boolean()));
			}

		}
	}
}