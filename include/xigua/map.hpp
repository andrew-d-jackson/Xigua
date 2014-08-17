#pragma once

#include <map>
#include <memory>

#include "xigua/data.hpp"

namespace xig {

class map : public data {
private:
  std::map<data_ptr, data_ptr> value;

public:
  map(std::map<data_ptr, data_ptr> value) : value(value) {}
  virtual ~map() {}

  virtual data_type type() const;
  virtual const map &as_map() const;

  std::map<data_ptr, data_ptr>::const_iterator begin() const;
  std::map<data_ptr, data_ptr>::const_iterator end() const;
  std::size_t size() const;

  operator std::map<data_ptr, data_ptr>() const;
  std::map<data_ptr, data_ptr> as_std_map() const;

  virtual bool operator<(const data &other) const;
  virtual bool operator==(const data &other) const;
};

extern bool map_equality(const std::map<data_ptr, data_ptr> &a,
                         const std::map<data_ptr, data_ptr> &b);

extern data_ptr make_map(std::map<data_ptr, data_ptr> val);
extern data_ptr make_map(std::vector<data_ptr> val);
}
