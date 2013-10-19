#pragma once

#include <vector>

#include "../data.hpp"
#include "../enviroment.hpp"
#include "../error.hpp"

#include "utils.hpp"

namespace xig {
namespace stdlib {

	class concatinate : public method {
		int amount_of_arguments() const { return 1; }
		bool has_repeating_arguments() const { return true; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			auto arguments = utils::parse_arguments(args, 1);

			std::string return_string = "";
			for (auto argument : arguments) {
				return_string += argument.as_string();
			}

			return data(data_type::string, return_string);
		}
	};

}}