#include "xigua/function.hpp"
#include "xigua/data.hpp"
#include "xigua/evaluate.hpp"

namespace xig {

data_ptr method::call(call_info fci) {

  if (should_evaluate_arguments()) {
    for (auto &item : fci.args) {
      if (item->type() == data_type::process ||
          item->type() == data_type::symbol ||
          item->type() == data_type::tuple || item->type() == data_type::map)
        item = evaluate(fci.env, item, fci.debug);
    }
  }

  if (has_repeating_arguments()) {
    std::vector<data_ptr> new_args(fci.args.begin(),
                                   fci.args.begin() + amount_of_arguments());

    auto repeating_args = xig::make_tuple(std::vector<data_ptr>(
        fci.args.begin() + amount_of_arguments(), fci.args.end()));

    new_args.push_back(repeating_args);

    fci.args = new_args;
  }

  return run(fci);
}

bool method::has_repeating_arguments() const { return false; }

bool method::has_process_arguments() const { return false; }

bool method::process_arguments_pass(call_info fci) { return true; }

bool method::should_evaluate_arguments() const { return true; }

bool method_set_comparator::operator()(const std::shared_ptr<method> &a,
                                       const std::shared_ptr<method> &b) {
  if (a->amount_of_arguments() < b->amount_of_arguments())
    return true;
  if (a->has_repeating_arguments() < b->has_repeating_arguments())
    return true;
  if (a->has_process_arguments() < b->has_process_arguments())
    return true;
  return false;
}

data_ptr function::call(call_info fci) const {

  for (auto iterator = methods.rbegin(); iterator != methods.rend();
       iterator++) {
    if ((unsigned)(*iterator)->amount_of_arguments() == fci.args.size()) {
      if ((*iterator)->has_process_arguments()) {
        try {
          if ((*iterator)->process_arguments_pass(fci))
            return (*iterator)->call(fci);
        } catch (error e) {
        }
      } else {
        return (*iterator)->call(fci);
      }
    } else if ((unsigned)(*iterator)->amount_of_arguments() < fci.args.size() &&
               (*iterator)->has_repeating_arguments()) {
      if ((*iterator)->has_process_arguments()) {
        if ((*iterator)->process_arguments_pass(fci))
          return (*iterator)->call(fci);
      } else {
        return (*iterator)->call(fci);
      }
    }
  }

  std::string error_message("Dosen't match a method overload in the specified "
                            "function.\nAmount of Args Passed: ");
  error_message += std::to_string(fci.args.size());
  error_message += "\nAmount of Args In Function: ";
  for (const auto &overload : methods) {
    error_message += std::to_string(overload->amount_of_arguments());
    if (overload->has_repeating_arguments())
      error_message += "r";
    if (overload->has_process_arguments())
      error_message += "p";
    error_message += " ";
  }

  throw error(error_type::invalid_arguments, error_message, fci.debug);
}
}
