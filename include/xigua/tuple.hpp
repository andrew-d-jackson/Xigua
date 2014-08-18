#pragma once

#include <vector>
#include <algorithm>
#include <memory>

#include "xigua/data.hpp"

namespace xig {

class base_tuple : public data {
private:
  std::vector<data_ptr> value;

public:
  base_tuple(std::vector<data_ptr> value) : value(value) {}
  virtual ~base_tuple() {}

  operator std::vector<data_ptr>() const;
  std::vector<data_ptr> as_std_vector() const;

  std::vector<data_ptr>::const_iterator begin() const;
  std::vector<data_ptr>::const_iterator end() const;
  std::size_t size() const;
  const data_ptr &at(std::size_t pos) const;

  virtual bool operator<(const data &other) const;

  virtual bool operator==(const data &other) const;
};

class tuple : public base_tuple {
public:
  tuple(std::vector<data_ptr> value) : base_tuple(value) {}
  virtual ~tuple() {}

  data_type type() const;
  const tuple &as_tuple() const;
};

extern data_ptr make_tuple(std::vector<data_ptr> val);
}
