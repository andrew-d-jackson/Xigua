#include "xigua/enviroment.hpp"

namespace xig
{

	enviroment::enviroment(env_type in_type)
	{
		type(in_type);
	}

	enviroment::enviroment(env_type in_type, enviroment * parent_enviroment)
	{
		type(in_type);

		if (in_type != env_type::Namespace)
		{
			if (parent_enviroment->type() != env_type::Namespace)
			{
				defined_variables = (*parent_enviroment).defined_variables;
				my_parent = parent_enviroment->parent();
			}
			else
			{
				my_parent = parent_enviroment;
			}
		}
		else
		{
			my_parent = parent_enviroment;
		}
	}

	void enviroment::type(env_type in_type) {
		my_type = in_type;
	};

	env_type enviroment::type() const {
		return my_type;
	};


	data* enviroment::find(std::string variable_name) {
		if (defined_variables.find(variable_name) != defined_variables.end())
			return &defined_variables[variable_name];

		if (parent() != nullptr)
		{
			auto data = parent()->find(variable_name);
			return data;
		}

		return nullptr;
	}

	void enviroment::set(std::string name, data value, bool force_here)
	{
		if (force_here) {
			defined_variables[name] = value;
		} else if (my_type == env_type::Namespace || my_type == env_type::Function) {
			defined_variables[name] = value;
		} else if (my_type == env_type::Macro || my_type == env_type::Let) {
			parent()->set(name, value);
		}
	}

	enviroment* enviroment::parent() const
	{
		return my_parent;
	};

	bool enviroment::has_parent() const
	{
		return (parent() != nullptr);
	}
	


}
