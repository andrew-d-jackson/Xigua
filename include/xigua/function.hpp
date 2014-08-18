#pragma once

#include <set>
#include <algorithm>
#include <functional>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/types.hpp"
#include "xigua/error.hpp"

namespace xig {

struct call_info {
  std::vector<data_ptr> args;
  enviroment &env;
  debug_info debug;
  call_info(std::vector<data_ptr> args, enviroment &env, debug_info debug)
      : args(args), env(env), debug(debug) {}
};

//! Abstract class that is the base for writing your own Xigua functions
class method {
public:
  virtual data_ptr run(call_info fci) = 0;
  virtual int amount_of_arguments() const = 0;
  virtual bool has_repeating_arguments() const;
  virtual bool has_process_arguments() const;
  virtual bool process_arguments_pass(call_info fci);
  virtual bool should_evaluate_arguments() const;

  data_ptr call(call_info fci);
};

//! Comparator used to sort methods internally
struct method_set_comparator {
  bool operator()(const std::shared_ptr<method> &a,
                  const std::shared_ptr<method> &b);
};

//! Class that repressents a function containing one or more methods
//! (overloads), when a function is called it decided what method overload is
//! run
class function : public data {
public:
  function() {};
  template <class T> function(T in_method) { add_method(in_method); }

  virtual ~function() {};

  virtual data_type type() const;
  virtual const function &as_function() const;
  virtual bool operator<(const data &other) const;
  virtual bool operator==(const data &other) const;


  template <class T> void add_method(T in_method) {
    insert_method(std::make_shared<T>(in_method));
  }

  void merge_with_function(const function &other);

  data_ptr call(call_info fci) const;

private:
  void insert_method(std::shared_ptr<method> in_method);

  std::vector<std::shared_ptr<method>> methods;
};

template <typename T> extern data_ptr make_function(T fn) {
  return std::make_shared<function>(fn);
}
}
