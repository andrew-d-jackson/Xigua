#pragma once

#include <set>
#include <algorithm>
#include <functional>
#include <memory>

#include "xigua/error.hpp"
#include "xigua/data.hpp"

namespace xig {

class data;
class enviroment;

struct debug_info {
  std::vector<std::string> function_call_list;
  debug_info() {
    function_call_list = {};
  }
  debug_info(std::vector<std::string> fcl) { function_call_list = fcl; }
};

struct call_info {
  std::vector<data> args;
  enviroment &env;
  debug_info debug;
  call_info(std::vector<data> args, enviroment &env, debug_info debug)
      : args(args), env(env), debug(debug) {}
};

//! Abstract class that is the base for writing your own Xigua functions
class method {
public:
  //! Stuff to be run when the method is called
  //! @param args the arguments passed to the function
  //! @param env the enviroment that the method is bieng run in
  //! @param fcl the function call list at the time the method was called
  virtual data run(call_info fci) = 0;

  //! The amount of arguments this method takes
  virtual int amount_of_arguments() const = 0;

  //! Wether this function can take unlimited arguments, all arguments beyond
  //! the amount specified in amount_of_arguments() will be condensed into a
  //! tuple and used as the final argument
  virtual bool has_repeating_arguments() const;

  //! Wether this method has any conditional arguments
  virtual bool has_process_arguments() const;

  //! If this method has any conditional arguments, is used to check wether the
  //! conditional arguments are met
  virtual bool process_arguments_pass(call_info fci);

  //! Wether this method should automatically lookup variables and execute
  //! processes, etc. before run() in called, defaults to true, should only be
  //! used in special cases when you want to ovveride the default arugment
  //! passing behaviour
  virtual bool should_evaluate_arguments() const;

  data call(call_info fci);
};

//! Comparator used to sort methods internally
struct method_set_comparator {
  bool operator()(const std::shared_ptr<method> &a,
                  const std::shared_ptr<method> &b);
};

//! Class that repressents a function containing one or more methods
//! (overloads), when a function is called it decided what method overload is
//! run
class function {
public:
  function() {};

  //! Constructs a function from a class that inherits method
  //! @param in_method class inheriting method that is the method
  template <class T> function(T in_method) { add_method(in_method); }

  //! Add a method (overload) to this function
  //! @param in_method class inheriting method that is the method
  template <class T> void add_method(T in_method) {
    insert_method(std::shared_ptr<T>(new T(in_method)));
  }

  //! Add all the methods from anothe function object to this function
  void merge_with_function(function other) {
    for (const std::shared_ptr<method> &i : other.methods) {
      insert_method(i);
    }
  }

  //! run when function is called, decides what method to call and then calls it
  //! @param args the arguments passed to the function
  //! @param env the enviroment that the method is bieng run in
  //! @param fcl the function call list at the time the method was called
  data call(call_info fci);

private:
  void insert_method(std::shared_ptr<method> in_method) {

    auto found = std::find_if(methods.begin(), methods.end(),
                              [&](std::shared_ptr<method> &a) {
      return (a->amount_of_arguments() == in_method->amount_of_arguments()) &&
             (a->has_repeating_arguments() ==
              in_method->has_repeating_arguments()) &&
             !a->has_process_arguments();
    });

    if (in_method->has_process_arguments() || found == methods.end()) {
      methods.push_back(in_method);
      std::sort(methods.begin(), methods.end(), method_set_comparator());
    } else {
      (*found) = in_method;
    }
  }

  std::vector<std::shared_ptr<method> > methods;
};
}
