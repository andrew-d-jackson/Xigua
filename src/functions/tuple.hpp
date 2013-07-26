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
		namespace Tuple
		{

			DataType join(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				bool repeating_args = false;
				if (inputs.size() > 2)
					repeating_args = true;

				DataType result(DataTypes::Tuple);

				if (inputs.at(0).type() == DataTypes::Tuple) {
					for (auto i : inputs.at(0).tuple())
						result.proc_push_back(i);
				} else { 
					result.proc_push_back(inputs.at(0));
				}

				if (inputs.at(1).type() == DataTypes::Tuple) {
					for (auto i : inputs.at(0).tuple())
						result.proc_push_back(i);
				} else { 
					result.proc_push_back(inputs.at(0));
				}

				if (repeating_args){
					for (const auto & input : inputs.at(2).tuple()) {
						result.proc_push_back(input);
					}
				}

				return result;
			}

		}
	}
}