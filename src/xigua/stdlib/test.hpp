#pragma once

#include <vector>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"

#include "xigua/stdlib/utils.hpp"


namespace xig {
namespace stdlib {

	class testeq : public method {
		int amount_of_arguments() const { return 3; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			if (args.at(0).type() != data_type::string)
				throw error(error_type::invalid_arguments, "Not A String", fcl);

			if (args.at(1) == args.at(2)) {
				std::cout << "Test Passed: " << args.at(0).as_string() << std::endl;
			} else {
				std::cout << "****" << std::endl
				<< "Test Failed: " << args.at(0).as_string() << std::endl
				<< "Args: " << string_representation(args.at(1)) << ", " << string_representation(args.at(2)) << std::endl
				<< "****" << std::endl;
			}

			return data(data_type::none);
		}
	};

	class testne : public method {
		int amount_of_arguments() const { return 3; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			if (args.at(0).type() != data_type::string)
				throw error(error_type::invalid_arguments, "Not A String", fcl);

			if (args.at(1) != args.at(2)) {
				std::cout << "Test Passed: " << args.at(0).as_string() << std::endl;
			} else {
				std::cout << "****" << std::endl
				<< "Test Failed: " << args.at(0).as_string() << std::endl
				<< "Args: " << string_representation(args.at(1)) << ", " << string_representation(args.at(2)) << std::endl
				<< "****" << std::endl;
			}

			return data(data_type::none);
		}
	};

	class testtr : public method {
		int amount_of_arguments() const { return 2; }

		data run(std::vector<data> args, enviroment & env, std::vector<std::string> fcl) {
			if (args.at(0).type() != data_type::string)
				throw error(error_type::invalid_arguments, "Not A String", fcl);
			
			if (args.at(1).type() != data_type::boolean)
				throw error(error_type::invalid_arguments, "Not A Boolean", fcl);

			if (args.at(1).as_boolean()) {
				std::cout << "Test Passed: " << args.at(0).as_string() << std::endl;
			} else {
				std::cout << "****" << std::endl
				<< "Test Failed: " << args.at(0).as_string() << std::endl
				<< "Args: " << string_representation(args.at(1)) << std::endl
				<< "****" << std::endl;
			}

			return data(data_type::none);
		}
	};


}}