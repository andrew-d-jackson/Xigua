#include "enviroment.hpp"

namespace xig
{

	Enviroment::Enviroment(EnvTypes enviroment_type)
	{
		type = enviroment_type;
	}

	Enviroment::Enviroment(EnvTypes enviroment_type, Enviroment * parent_enviroment)
	{
		type = enviroment_type;

		if (enviroment_type != EnvTypes::Namespace)
		{
			if (parent_enviroment->type != EnvTypes::Namespace)
			{
				defined_variables = (*parent_enviroment).defined_variables;
				parent = parent_enviroment->parent;
			}
			else
			{
				parent = parent_enviroment;
			}
		}
		else
		{
			parent = parent_enviroment;
		}
	}

	data* Enviroment::find(std::string variable_name) {
		if (defined_variables.find(variable_name) != defined_variables.end())
			return &defined_variables[variable_name];

		if (parent != nullptr)
		{
			auto data = parent->find(variable_name);
			return data;
		}

		return nullptr;
	}

	void Enviroment::set(std::string name, data value, bool force_here)
	{
		if (force_here) {
			defined_variables[name] = value;
		} else if (type == EnvTypes::Namespace || type == EnvTypes::Function) {
			defined_variables[name] = value;
		} else if (type == EnvTypes::Macro || type == EnvTypes::Let) {
			parent->set(name, value);
		}
	}

	std::map<std::string, data> Enviroment::get_all_defined_variables() const
	{
		return get_defined_variables();

	};

	bool Enviroment::has_parent() const
	{
		return (parent != nullptr);
	}
	
	Enviroment* Enviroment::get_parent() const
	{
		return parent;
	};

	std::map<std::string, data> Enviroment::get_defined_variables() const
	{
		return defined_variables;
	};


}
