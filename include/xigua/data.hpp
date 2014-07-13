#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <map>
#include <tuple>
#include <utility>
#include <memory>

#include "xigua/enviroment.hpp"

#include "xigua/error.hpp"

#include "xigua/function.hpp"

namespace xig {

//! Enum for the different kinds of Xigua data types
enum class data_type {

  //! Represents none/nil/nothing, returned by empty function
  none,
  //! Represents the name of a variable, not an actual data type, just used by
  //! interpreter
  symbol,
  //! Represents a true/false value
  boolean,
  //! Represents a string of charicters, can contain spaces/newlines/etc
  string,
  //! Represents a string of charicters, usually one word, can't contain
  //! spaces/newlines/etc, typically used as a key in a map
  keyword,
  //! Represents a floating point number
  integer,
  //! Represents a floating point number
  decimal,
  //! Represents a list containing any number of elements and types, can contain
  //! data of multiple types in the same tuple
  tuple,
  //! Represents a hash map of keys and values, can contain keys/values of
  // multiple types in the same map
  map,
  //! Represents a unexecuted process, not an actual data type, just used by
  //! intepreter
  process,
  //! Represents a function of a single method or multiple overloads
  function,
  //! Represents an enviroment containing variables, not an actual data type,
  //! just used by intepreter
  container
};

class data;
class function;
class enviroment;

//! Generic class that holds all Xigua data types
class data {
protected:
  data_type my_type;
  void* data_pointer;

public:
  data();
  ~data();
  data(const data& other);
  data(long long number);
  data(long double number);
  data(bool boolean_data);
  data(function function_data);
  data(enviroment container_data);
  data(std::map<data, data> map_data);
  data(data_type in_type, std::string string_data);
  data(data_type in_type, std::vector<data> list_data);

  data& operator=(const data &other);
  bool operator==(const data &other) const;
  bool operator!=(const data &other) const;
  bool operator<(const data &other) const;

  operator bool() const;
  operator long long() const;
  operator long double() const;
  operator std::string() const;
  operator std::map<data, data>() const;
  operator function() const;
  operator enviroment *() const;

  //! Get the type of the data
  data_type type() const;

  //! Get a copy data as a std::string, assumes type is string
  std::string as_string() const;
  //! Get a copy data as a std::string, assumes type is symbol
  std::string as_symbol() const;
  //! Get a copy data as a std::string, assumes type is keyword, won't include :
  std::string as_keyword() const;
  //! Get a copy data as a long double, assumes type is decimal
  long double as_decimal() const;
  //! Get a copy data as a long double, assumes type is number
  long long as_integer() const;
  //! Get a copy data as a std::vector of data, assumes type is integer
  std::vector<data> as_tuple() const;
  //! Get a copy data as a std::map of data as the key and the value, assumes
  // type is map
  std::map<data, data> as_map() const;
  //! Get a copy data as a std::vector of data, assumes type is process
  std::vector<data> as_process() const;
  //! Get a copy data as a bool, assumes type is boolean
  bool as_boolean() const;
  //! Get a copy data as a function, assumes type is function
  function as_function() const;
  //! Get a copy data as an enviroment pointer, assumes type is container
  enviroment *as_container() const;

private:
	void delete_pointer();
	void assign_from_other(const data &other);
};

//! Get a nice string representation of a data object
extern std::string string_representation(const data &in_data);

//! Helper function to make data of type number
extern data make_decimal(long double num);

//! Helper function to make data of type number
extern data make_integer(long long num);

//! Helper function to make data of type string
extern data make_string(std::string str);

//! Helper function to make data of type symbol
extern data make_symbol(std::string str);

//! Helper function to make data of type keyword
extern data make_keyword(std::string str);

//! Helper function to make data of type boolean
extern data make_boolean(bool b);

//! Helper function to make data of type none
extern data make_none();

//! Helper function to make data of type tuple
extern data make_tuple(std::vector<data> tuple);

//! Helper function to make data of type process
extern data make_process(std::vector<data> proc);

//! Helper function to make data of type map
extern data make_map(std::map<data, data> map);

//! Helper function to make data of type container from an enviroment
extern data make_container(enviroment container);

//! Helper function to make data of type blank container
extern data make_container();

//! Helper function to make data of type function
template <typename T> extern data make_function(T fn) { return function(fn); }
}
