#pragma once

#include <string>
#include <map>

#include "datatype.hpp"


namespace Xigua
{
	class DataType;
	class Enviroment
	{
	public:
		std::map<std::string, DataType> defined_variables;
		Enviroment * parent_eviroment;
		bool is_function_enviroment;

		Enviroment() : parent_eviroment(nullptr), is_function_enviroment(false){}
		Enviroment(Enviroment * parent) : parent_eviroment(parent), is_function_enviroment(false){}
		Enviroment(Enviroment * parent, bool function_argument);
		

		DataType* find(std::string variable_name);
		void set(std::string name, DataType value);
	};
}
