#pragma once

#include <vector>
#include <map>
#include <sstream>
#include <memory>

#include "xigua/error.hpp"

namespace xig {

enum class data_type {
  none,
  symbol,
  boolean,
  string,
  keyword,
  integer,
  decimal,
  tuple,
  map,
  process,
    record_definition,
    record_object,
  function,
  enviroment
};

class data;
class boolean;
class symbol;
class none;
class string;
class decimal;
class integer;
class tuple;
class map;
class process;
class function;
class enviroment;
    class keyword;
    class record_definition;
    class record_object;

typedef std::shared_ptr<const data> data_ptr;

class data {
public:
  virtual ~data() {}

  virtual data_type type() const = 0;

  virtual bool operator<(const data &other) const = 0;
  virtual bool operator==(const data &other) const = 0;
  virtual bool operator!=(const data &other) const {
    return !(*this == other);
  };

  virtual const boolean &as_boolean() const { throw; }
  virtual const tuple &as_tuple() const { throw; }
  virtual const integer &as_integer() const { throw; }
  virtual const decimal &as_decimal() const { throw; }
  virtual const map &as_map() const { throw; }
  virtual const string &as_string() const { throw; }
  virtual const symbol &as_symbol() const { throw; }
  virtual const keyword &as_keyword() const { throw; }
  virtual const process &as_process() const { throw; }
  virtual const none &as_none() const { throw; }
  virtual const enviroment &as_enviroment() const { throw; }
  virtual const function &as_function() const { throw; }
  virtual const record_definition &as_record_definition() const { throw; }
    virtual const record_object &as_record_object() const { throw; }
};

extern std::string string_representation(const data_ptr &d);
}
