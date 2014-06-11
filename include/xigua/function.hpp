#pragma once

#include <set>
#include <algorithm>
#include <functional>
#include <memory>

#include "xigua/error.hpp"

namespace xig {

class data;
class enviroment;

//! Abstract class that is the base for writing your own Xigua functions
class method {
public:
  virtual data run(std::vector<data>, enviroment &,
                   std::vector<std::string>) = 0;

  virtual int amount_of_arguments() const = 0;
  virtual bool has_repeating_arguments() const;
  virtual bool has_process_arguments() const;
  virtual bool process_arguments_pass(std::vector<data> args, enviroment &env, std::vector<std::string> fcl);
  virtual bool should_evaluate_arguments() const;

  data call(std::vector<data> arguments, enviroment &enviroment,
            std::vector<std::string> function_call_list);
};

struct method_set_comparator {
  bool operator()(const std::shared_ptr<method> &a,
                  const std::shared_ptr<method> &b);
};

class function {
public:
  function() {};

  void insert_method(std::shared_ptr<method> in_method) {

	  auto found = std::find_if(methods.begin(), methods.end(), [&](std::shared_ptr<method> &a){
		  return (a->amount_of_arguments() == in_method->amount_of_arguments()) &&
			  (a->has_repeating_arguments() == in_method->has_repeating_arguments());
	  });

	  if (in_method->has_process_arguments() || found == methods.end()) {
		  methods.push_back(in_method);
		  std::sort(methods.begin(), methods.end(), method_set_comparator());
	  }
	  else {
		//  *found = in_method;
	  }
  }

  template <class T> function(T in_method) { add_method(in_method); }

  template <class T> void add_method(T in_method) {
	  insert_method(std::shared_ptr<T>(new T(in_method)));
  }

  void merge_with_function(function other) {
    for (const std::shared_ptr<method> &i : other.methods) {
	  insert_method(i);
    }
  }

  data call(std::vector<data> &args, enviroment &enviroment,
            std::vector<std::string> function_call_list);

private:
  std::vector<std::shared_ptr<method>> methods;
};
}
