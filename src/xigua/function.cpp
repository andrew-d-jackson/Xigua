#include "xigua/function.hpp"


#include "xigua/evaluate.hpp"
#include "xigua/data.hpp"

namespace xig {

	data method::call(std::vector<data> arguments, enviroment & enviroment, std::vector<std::string> function_call_list) {

		if (should_evaluate_arguments()) {
			for (auto & item : arguments) {
				if (item.type() == data_type::process || item.type() == data_type::symbol || item.type() == data_type::tuple || item.type() == data_type::map)
					item = evaluate(enviroment, item, function_call_list);
			}
		}

		if (has_repeating_arguments()) {
			std::vector<data> new_args(arguments.begin(), arguments.begin() + amount_of_arguments()); 
			data repeating_args(data_type::tuple, std::vector<data>(arguments.begin() + amount_of_arguments(), arguments.end()));
			new_args.push_back(repeating_args);

			arguments = new_args;
		}

		return run(arguments, enviroment, function_call_list);

	}

	bool method::has_repeating_arguments() const {
		return false;
	}

	bool method::should_evaluate_arguments() const {
		return true;
	}

	bool method_set_comparator::operator() (const std::shared_ptr<method> & a, const std::shared_ptr<method> & b) {
		if (a->amount_of_arguments() < b->amount_of_arguments())
			return true;
		if (a->has_repeating_arguments() < b->has_repeating_arguments())
			return true;
		return false;
	}

	data function::call(std::vector<data> & args, enviroment & enviroment, std::vector<std::string> function_call_list) {

		for(auto iterator = methods.rbegin(); iterator != methods.rend(); iterator++) {
			if ((*iterator)->amount_of_arguments() == args.size())
				return (*iterator)->call(args, enviroment, function_call_list);
			else if ((*iterator)->amount_of_arguments() < args.size() && (*iterator)->has_repeating_arguments())
				return (*iterator)->call(args, enviroment, function_call_list);
		}


		std::stringstream error_message ("dosen't match a method overload in function. Amount of Args Passed:");
		error_message << (int)args.size();
		throw error(error_types::invalid_arguments, error_message.str(), function_call_list);
	}

	
}