#pragma once

#include <string>
#include <map>

#include "datatype.hpp"


namespace Xigua
{
	class DataType;

	enum class EnvTypes { Namespace, Function, Macro, Let };

	class Enviroment
	{
	public:
		std::map<std::string, DataType> defined_variables;
		Enviroment * parent;
		EnvTypes type;

		Enviroment(EnvTypes type);
		Enviroment(EnvTypes type, Enviroment * parent);
		

		DataType* find(std::string variable_name);
		void set(std::string name, DataType value, bool force_here = false);

		std::map<std::string, DataType> get_all_defined_variables() const;

		bool has_parent() const;
		Enviroment* get_parent() const;
		std::map<std::string, DataType> get_defined_variables() const;

	};
}
