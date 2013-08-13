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
		namespace Containers
		{

			DataType at(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() == DataTypes::Number && inputs.at(1).type() == DataTypes::Tuple) {
					if (inputs.at(0).number() < 0  || inputs.at(0).number() > inputs.at(1).tuple().size() - 1)
						Xigua::FunctionUtils::misc_error("at", "not in rage of tuple");
					return inputs.at(1).tuple().at(inputs.at(0).number());
				} else if (inputs.at(1).type() == DataTypes::HashMap) {
					auto map = inputs.at(1).hash_map();
					auto location = map.find(inputs.at(0));
					if (location != map.end()) {
						return location->second;
					} else {
						Xigua::FunctionUtils::misc_error("at", "not in hashmap");
					}
				} else {
					Xigua::FunctionUtils::wrong_type_error("at");
				}
				return DataTypes::None;
			}

			DataType size(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() == DataTypes::Tuple)
					return DataType(DataTypes::Number, (long double)inputs.at(0).tuple().size());

				if (inputs.at(0).type() == DataTypes::HashMap)
					return DataType(DataTypes::Number, (long double)inputs.at(0).hash_map().size());

				Xigua::FunctionUtils::wrong_type_error("size");
				return DataTypes::None;
			}

		}
	}
}