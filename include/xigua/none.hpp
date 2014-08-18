#pragma once

#include <iostream>
#include <memory>

#include "xigua/data.hpp"
#include "xigua/error.hpp"

namespace xig {

class none : public data {
public:
  virtual ~none() {}

  virtual data_type type() const;

  virtual const none &as_none() const;

  virtual bool operator<(const data &other) const;
  virtual bool operator==(const data &other) const;
};

extern data_ptr make_none();
}
