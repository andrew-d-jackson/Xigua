#include "xigua/map.hpp"

namespace xig {

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
