#pragma once

#include <string>
#include <map>

#include "xigua/data.hpp"


namespace xig
{
	class data;

	enum class env_type { Namespace, Function, Macro, Let };

	class enviroment {
	public:
		enviroment(env_type in_type);
		enviroment(env_type in_type, enviroment * parent);

		env_type type() const;
		void type(env_type in_type);

		data* find(std::string variable_name);
		void set(std::string name, data value, bool force_here = false);

		enviroment* parent() const;
		bool has_parent() const;


	private:
		std::map<std::string, data> defined_variables;
		enviroment * my_parent;
		env_type my_type;
	};
}
