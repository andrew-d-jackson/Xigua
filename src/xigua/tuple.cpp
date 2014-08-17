#include "xigua/tuple.hpp"

namespace xig {

base_tuple::operator std::vector<data_ptr>() const { return value; }

std::vector<data_ptr> base_tuple::as_std_vector() const { return value; }

std::vector<data_ptr>::const_iterator base_tuple::begin() const {
  return value.cbegin();
}

std::vector<data_ptr>::const_iterator base_tuple::end() const { return value.cend(); }

const data_ptr &base_tuple::at(std::size_t pos) const { return value.at(pos); }

std::size_t base_tuple::size() const { return value.size(); }

bool base_tuple::operator<(const data &other) const {
  if (type() == other.type())
    return (value < static_cast<const base_tuple &>(other).value);
  return type() < other.type();
}

bool base_tuple::operator==(const data &other) const {
  if (type() == other.type()) {
    const auto &otherValue = static_cast<const base_tuple &>(other).value;
    return std::equal(
        value.begin(), value.end(), otherValue.begin(),
        [](const data_ptr &a, const data_ptr &b) { return *a == *b; });
  }
  return false;
}

data_type tuple::type() const { return data_type::tuple; }

const tuple &tuple::as_tuple() const { return *this; }

data_ptr make_tuple(std::vector<data_ptr> val) {
  return std::make_shared<tuple>(val);
}
}
