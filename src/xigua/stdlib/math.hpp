#pragma once

#include <vector>
#include <cmath>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"

#include "xigua/stdlib/utils.hpp"

namespace xig {
namespace stdlib {

	class comparator : public method {
		int amount_of_arguments() const { return 2; }
		bool has_repeating_arguments() const { return true; }

		virtual bool all_types_must_be_numbers() const { return true; }

		virtual bool compare (data a, data b) const = 0;

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			auto arguments = utils::parse_arguments(args, 2);
			if (!utils::all_types_are(arguments, data_type::number) && all_types_must_be_numbers())
				throw error(error_types::invalid_arguments, "Not A Number", fcl);

			for (auto it = arguments.begin(); it < arguments.end()-1; it++) {
				if (!compare(*it, *(it+1)))
					return data(data_type::boolean, false);
			}
			return data(data_type::boolean, true);
		}
	};

	class less_than : public comparator {
		bool compare(data a, data b) const {
			return (a.as_number() < b.as_number());
		}
	};

	class greater_than : public comparator {
		bool compare(data a, data b) const {
			return (a.as_number() > b.as_number());
		}
	};

	class less_than_or_equal : public comparator {
		bool compare(data a, data b) const {
			return (a.as_number() <= b.as_number());
		}
	};

	class greater_than_or_equal : public comparator {
		bool compare(data a, data b) const {
			return (a.as_number() >= b.as_number());
		}
	};

	class equal_to : public comparator {
		bool all_types_must_be_numbers() const { return false; }
		bool compare(data a, data b) const {
			return (a == b);
		}
	};

	class math_operation : public method {
		int amount_of_arguments() const { return 2; }
		bool has_repeating_arguments() const { return true; }

		virtual long double operate (long double a, long double b) const = 0;

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			auto arguments = utils::parse_arguments(args, 2);
			if (!utils::all_types_are(arguments, data_type::number))
				throw error(error_types::invalid_arguments, "Not A Number", fcl);

			long double return_value = arguments.at(0).as_number();
			for (auto it = arguments.begin()+1; it < arguments.end(); it++) {
				return_value = operate(return_value, it->as_number());
			}
			return data(data_type::number, return_value);
		}
	};

	class add : public math_operation {
		long double operate(long double a, long double b) const {
			return a+b;
		}
	};

	class minus : public math_operation {
		long double operate(long double a, long double b) const {
			return a-b;
		}
	};

	class multiply : public math_operation {
		long double operate(long double a, long double b) const {
			return a*b;
		}
	};

	class divide : public math_operation {
		long double operate(long double a, long double b) const {
			return a/b;
		}
	};

	class modulo : public method {
		int amount_of_arguments() const { return 2; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {			
			if (!utils::all_types_are(args, data_type::number))
				throw error(error_types::invalid_arguments, "Not A Number", fcl);

			return make_number(std::fmod(args.at(0).as_number(), args.at(1).as_number()));
		}
	};
}}