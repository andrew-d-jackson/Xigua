#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <limits>

#include "../datatype.hpp"
#include "../enviroment.hpp"
#include "../functionutils.hpp"


namespace Xigua
{
	namespace Functions
	{
		namespace String
		{

			DataType concatinate(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				auto arguments = Xigua::FunctionUtils::parse_arguments(inputs, 1);

				std::string return_string = "";
				for (auto argument : arguments) {
					if (argument.type() == DataTypes::String) {
						return_string += argument.string();
					} else if (argument.type() == DataTypes::Bool){
						if (argument.boolean()) {
							return_string += "true";
						} else {
							return_string += "false";
						}
					} else if (argument.type() == DataTypes::Number){
						std::stringstream ss;
						ss << argument.number();
						return_string += ss.str();
					} else {
						Xigua::FunctionUtils::wrong_type_error("string");
					}
				}

				return DataType(DataTypes::String, return_string);
			}

		}
	}
}