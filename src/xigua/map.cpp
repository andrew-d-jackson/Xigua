#include "xigua/map.hpp"

namespace xig {

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
