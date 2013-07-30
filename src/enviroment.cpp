#include "enviroment.hpp"


namespace Xigua
{

	Enviroment::Enviroment(Enviroment * parent, bool function_argument)
	{
		is_function_enviroment = function_argument;

		if (parent->is_function_enviroment)	{
			defined_variables = (*parent).defined_variables;
			parent_eviroment = parent->parent_eviroment;
		} else {
			parent_eviroment = parent;
		}
	}


	DataType* Enviroment::find(std::string variable_name) {
		if (defined_variables.find(variable_name) != defined_variables.end())
			return &defined_variables[variable_name];

		if (parent_eviroment != nullptr)
		{
			auto data = parent_eviroment->find(variable_name);
			return data;
		}

		return nullptr;
	}

	void Enviroment::set(std::string name, DataType value)
	{
		defined_variables[name] = value;
	}

}
