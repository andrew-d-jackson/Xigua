#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

template <class T> class optional {
private:
  std::shared_ptr<T> ptr;

public:
  optional() { ptr = std::shared_ptr<T>(nullptr); }
  optional(const T &obj) { ptr = std::make_shared<T>(obj); }

  operator bool() const { return ptr; }
  bool contains_value() const { return ptr; }

  const T &unwrap() const {
    if (ptr)
      return *ptr;
    throw;
  };
};

template <class Iter>
void for_each_ref(Iter begin, Iter end, std::function<void(const data &)> fn) {
  for (it = begin; it != end; it++) {
    fn(**it);
  }
}

void for_each_ref(const std::vector<data_ptr> &ptrs,
                  std::function<void(const data &)> fn) {
  return for_each_ref(ptrs.begin(), ptrs.end(), fn);
}

void for_each_ref(const data_ptr &ptr, std::function<void(const data &)> fn) {
  if (ptr->type() == data_type::tuple) {
    auto ptr_val = ptr->as_tuple();
    return for_each_ref(ptr_val.begin(), ptr_val.end(), fn);
  } else if (ptr->type() == data_type::process) {
    auto ptr_val = ptr->as_process();
    return for_each_ref(ptr_val.begin(), ptr_val.end(), fn);
  }
  throw;
}

template <class Iter>
void for_each_ref(Iter begin, Iter end,
                  std::function<void(const data &, const data &)> fn) {
  for (it = begin; it != end; it++) {
    fn(*((*it)->first), *((*it)->second));
  }
}

void for_each_ref(const std::map<data_ptr, data_ptr> &ptrs,
                  std::function<void(const data &, const data &)> fn) {
  return for_each_ref(ptrs.begin(), ptrs.end(), fn);
}

void for_each_ref(const data_ptr &ptr,
                  std::function<void(const data &, const data &)> fn) {
  if (ptr->type() == data_type::map) {
    auto ptr_val = ptr->as_map();
    return for_each_ref(ptr_val.begin(), ptr_val.end(), fn);
  }
  throw;
}
}
