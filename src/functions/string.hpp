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
		namespace String
		{

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