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


			DataType to_string(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() == DataTypes::String)
					return inputs.at(0);

				if (inputs.at(0).type() == DataTypes::Bool){
					if (inputs.at(0).boolean())
						return DataType(DataTypes::String, "true");
					else
						return DataType(DataTypes::String, "false");
				}

				if (inputs.at(0).type() == DataTypes::Number){
					std::stringstream ss;
					ss << inputs.at(0).number();
					return DataType(DataTypes::String, ss.str());
				}
			
				std::cout << "Incompatible Type in to string";
				exit(1);
			}


			DataType concatinate(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::String || inputs.at(1).type() != DataTypes::String) {
					std::cout << "Not a String";
					exit(1);
				}
				bool repeating_args = false;
				if (inputs.size() > 2) {
					repeating_args = true;
					for (auto item : inputs.at(2).tuple()){
						if (item.type() != DataTypes::String){
							std::cout << "Not a String";
							exit(1);
						}
					}

				}

				std::string result = inputs.at(0).string();
				result += inputs.at(1).string();

				if (repeating_args){
					for (const auto & input : inputs.at(2).tuple()) {	
						result += input.string();
					}
				}

				return DataType(DataTypes::String, result);
			}

		}
	}
}