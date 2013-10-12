#pragma once

#include <string>
#include <map>

#include "datatype.hpp"


namespace xig
{
	class data;

	enum class EnvTypes { Namespace, Function, Macro, Let };

	class Enviroment
	{
	public:
		std::map<std::string, data> defined_variables;
		Enviroment * parent;
		EnvTypes type;

		Enviroment(EnvTypes type);
		Enviroment(EnvTypes type, Enviroment * parent);
		

		data* find(std::string variable_name);
		void set(std::string name, data value, bool force_here = false);

		std::map<std::string, data> get_all_defined_variables() const;

		bool has_parent() const;
		Enviroment* get_parent() const;
		std::map<std::string, data> get_defined_variables() const;

	};
}
