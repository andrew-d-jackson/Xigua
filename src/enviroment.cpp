#include "enviroment.hpp"


namespace Xigua
{

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
