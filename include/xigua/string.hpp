#pragma once

#include <string>
#include <memory>

#include "xigua/data.hpp"

namespace xig {

class base_string : public data {
private:
  std::string value;

public:
  base_string(std::string value) : value(value) {}
  virtual ~base_string() {}

  operator std::string() const;
  std::string as_std_string() const;

  std::string::const_iterator begin() const;
  std::string::const_iterator end() const;

  virtual bool operator<(const data &other) const;
  virtual bool operator==(const data &other) const;
};

class string : public base_string {
public:
  string(std::string value) : base_string(value) {}
  virtual ~string() {}

  virtual data_type type() const;
  virtual const string &as_string() const;
};

extern data_ptr make_string(std::string str);
}
