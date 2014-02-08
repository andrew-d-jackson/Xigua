#pragma once

#include <string>
#include <map>

#include "xigua/data.hpp"


namespace xig
{
	class data;

	enum class env_type { container, function, macro, let };

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

		std::string relative_path() const;
		void set_relative_path(std::string path);

	private:
		std::map<std::string, data> defined_variables;
		enviroment * my_parent;
		env_type my_type;
		std::string my_relative_path;
	};
}
