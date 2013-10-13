#include "containers.hpp"


namespace xig {
namespace stdlib {

	data at(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		if (inputs.at(0).type() == data_type::Number && inputs.at(1).type() == data_type::Tuple) {
			if (inputs.at(0).number() < 0  || inputs.at(0).number() > inputs.at(1).tuple().size() - 1)
				throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not In Range Of Tuple", function_call_list);
			return inputs.at(1).tuple().at((unsigned int)inputs.at(0).number());
		} else if (inputs.at(1).type() == data_type::HashMap) {
			auto map = inputs.at(1).hash_map();
			auto location = map.find(inputs.at(0));
			if (location != map.end()) {
				return location->second;
			} else {
				throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not In HashMap", function_call_list);
			}
		} else {
			throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A HashMap Or A Tuple", function_call_list);
		}
		return data_type::None;
	}

	data size(std::vector<data> inputs, enviroment* execution_enviroment, std::vector<std::string> function_call_list)
	{
		if (inputs.at(0).type() == data_type::Tuple)
			return data(data_type::Number, (long double)inputs.at(0).tuple().size());

		if (inputs.at(0).type() == data_type::HashMap)
			return data(data_type::Number, (long double)inputs.at(0).hash_map().size());

		throw xig::Error(xig::ErrorTypes::INVALID_ARGS, "Not A HashMap Or A Tuple", function_call_list);
		return data_type::None;
	}

}}