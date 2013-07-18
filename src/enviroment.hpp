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

		Enviroment() : parent_eviroment(nullptr){}
		Enviroment(Enviroment * parent) : parent_eviroment(parent){}

		DataType* find(std::string variable_name);
		void set(std::string name, DataType value);
	};
}