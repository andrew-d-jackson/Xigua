#pragma once

#include <vector>

#include "../data.hpp"
#include "../enviroment.hpp"
#include "../error.hpp"

#include "utils.hpp"


namespace xig {
namespace stdlib {

	class boolean_not : public method {
		int amount_of_arguments() const { return 1; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			if (args.at(0).type() != data_type::boolean)
				throw error(error_types::invalid_arguments, "Not A Boolean", fcl);

			return data(data_type::boolean, !(args.at(0).boolean()));
		}
	};


}}