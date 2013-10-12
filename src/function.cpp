#include "function.hpp"


#include "datatype.hpp"

namespace xig {


	method::method(int in_amount_of_args, xigua_lambda_t in_lambda) {
		amount_of_args = in_amount_of_args;
		lambda = in_lambda;
		should_evaluate = true;
		repeating = false;
	}

	method::method(int in_amount_of_args, bool in_repeating, xigua_lambda_t in_lambda) {
		amount_of_args = in_amount_of_args;
		repeating = in_repeating;
		lambda = in_lambda;
		should_evaluate = true;
	}

	method::method(int in_amount_of_args, bool in_repeating, bool in_should_evaluate, xigua_lambda_t in_lambda) {
		amount_of_args = in_amount_of_args;
		repeating = in_repeating;
		lambda = in_lambda;
		should_evaluate = in_should_evaluate;
	}

	data method::call(std::vector<data> arguments, enviroment * enviroment, std::vector<std::string> function_call_list) const {

		if (should_evaluate) {
			for (auto & item : arguments) {
				if (item.type() == data_type::Proc || item.type() == data_type::Symbol || item.type() == data_type::Tuple || item.type() == data_type::HashMap)
					item = item.evaluate(enviroment, function_call_list);
			}
		}

		if (repeating) {
			std::vector<data> new_args(arguments.begin(), arguments.begin() + amount_of_args); 
			data repeating_args(data_type::Tuple, std::vector<data>(arguments.begin() + amount_of_args, arguments.end()));
			new_args.push_back(repeating_args);

			arguments = new_args;
		}

		return lambda(arguments, enviroment, function_call_list);

	}


	bool method::operator==(method other) const {
		return (amount_of_args == other.amount_of_args && repeating == other.repeating);
	}

	bool method::operator!=(method other) const {
		return !(*this == other);
	}

	bool method::operator<(method other) const {
		if (amount_of_args < other.amount_of_args)
			return true;
		else if (repeating < other.repeating)
			return true;
		return false;
	}

	int method::amount_of_arguments() const {
		return amount_of_args;
	};

	bool method::has_repeating_arguments() const {
		return repeating;
	}


	function::function(method in_method) {
		add_method(in_method);
	}


	void function::add_method(method in_method) {
		methods.insert(in_method);
	}

	data function::call(std::vector<data> & args, enviroment * enviroment, std::vector<std::string> function_call_list) {

		for(auto iterator = methods.rbegin(); iterator != methods.rend(); iterator++) {
			if (iterator->amount_of_arguments() == args.size())
				return iterator->call(args, enviroment, function_call_list);
			else if (iterator->amount_of_arguments() < args.size() && iterator->has_repeating_arguments())
				return iterator->call(args, enviroment, function_call_list);
		}


		std::stringstream error_message ("dosen't match a method overload in function. Amount of Args Passed:");
		error_message << (int)args.size();
		throw Error(ErrorTypes::INVALID_ARGS, error_message.str(), function_call_list);
	}

	
}