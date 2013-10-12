#pragma once

#include <set>
#include <functional>

#include "error.hpp"

namespace xig {

	class data;
	class enviroment;

	typedef std::function<data(std::vector<data>, enviroment*, std::vector<std::string>)> xigua_lambda_t;

	class method {
	public:
		method(int amount_of_args, xigua_lambda_t lambda);
		method(int amount_of_args, bool repeating, xigua_lambda_t lambda);
		method(int amount_of_args, bool repeating, bool should_evaluate, xigua_lambda_t lambda);

		data call(std::vector<data> arguments, enviroment * enviroment, std::vector<std::string> function_call_list) const;

		bool operator==(method other) const;
		bool operator!=(method other) const;
		bool operator<(method other) const;

		int amount_of_arguments() const;
		bool has_repeating_arguments() const;

	private:
		int amount_of_args;
		bool repeating;
		bool should_evaluate;
		xigua_lambda_t lambda;
	};

	class function {
		public:
			function(){};
			function(method in_method);

			void add_method(method in_method);
			data call(std::vector<data> & args, enviroment * enviroment, std::vector<std::string> function_call_list);

		private:
			std::set<method> methods;
	};

}
