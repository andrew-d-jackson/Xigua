#include "xigua/map.hpp"

namespace xig {

data_type map::type() const { return data_type::map; };

const map &map::as_map() const { return *this; }

std::map<data_ptr, data_ptr>::const_iterator map::begin() const { return value.cbegin(); }

std::map<data_ptr, data_ptr>::const_iterator map::end() const { return value.cend(); }

std::size_t map::size() const { return value.size(); }

map::operator std::map<data_ptr, data_ptr>() const { return value; }

std::map<data_ptr, data_ptr> map::as_std_map() const { return value; }

bool map::operator<(const data &other) const {
  if (type() == other.type())
    return (value < other.as_map().value);
  return type() < other.type();
}

bool map::operator==(const data &other) const {
  if (type() == other.type())
    return map_equality(value, other.as_map().value);
  return false;
}

bool map_equality(const std::map<data_ptr, data_ptr> &a,
                  const std::map<data_ptr, data_ptr> &b) {

  for (const auto &pair : a) {
    const auto &key = *pair.first;
    const auto &value = *pair.second;

    bool contains_match = false;

    for (const auto &second_pair : b) {
      if (*second_pair.first == key && *second_pair.second == value) {
        contains_match = true;
        break;
      }
    }

    if (!contains_match)
      return false;
  }
  return true;
}

data_ptr make_map(std::map<data_ptr, data_ptr> val) {
  return std::make_shared<map>(val);
}

data_ptr make_map(std::vector<data_ptr> val) {
  std::map<data_ptr, data_ptr> temp_map;
  for (unsigned int i(0); i + 1 < val.size(); i += 2) {
    temp_map[val.at(i)] = val.at(i + 1);
  }
  return make_map(std::map<data_ptr, data_ptr>(temp_map));
}
}
