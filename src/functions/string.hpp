#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <limits>

#include "../datatype.hpp"
#include "../enviroment.hpp"


namespace Xigua
{
	namespace Functions
	{
		namespace String
		{

			std::string as_string(DataType input)
			{
				if (input.type() == DataTypes::String)
					return input.string();

				if (input.type() == DataTypes::Bool){
					if (input.boolean())
						return "true";
					else
						return "false";
				}

				if (input.type() == DataTypes::Number){
					std::stringstream ss;
					ss << input.number();
					return ss.str();
				}

				return "";
			}


			DataType concatinate(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				std::vector<DataType> arguments;
				for (auto input : inputs) {
					if(input.type() == DataTypes::Tuple) {
						for (auto i : input.tuple()) {
							arguments.push_back(i);
						}
					} else {
						arguments.push_back(input);
					}
				}

				std::string return_string = "";
				for (auto argument : arguments) {
					return_string += as_string(argument);
				}

				return DataType(DataTypes::String, return_string);
			}

		}
	}
}