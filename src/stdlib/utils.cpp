#include "stdlib/utils.hpp"

namespace xig {
namespace stdlib {
namespace utils {

std::vector<data_ptr> parse_arguments(std::vector<data_ptr> arguments,
                                      unsigned int nonrepeating) {
  std::vector<data_ptr> return_list;
  for (unsigned int i(0); i < arguments.size(); i++) {
    if (i < nonrepeating) {
      return_list.push_back(arguments.at(i));
    } else {
      for (auto j : arguments.at(i)->as_tuple().as_std_vector())
        return_list.push_back(j);
    }
  }

  return return_list;
}

bool all_types_are(std::vector<data_ptr> arguments, data_type expected) {
  for (auto argument : arguments) {
    if (argument->type() != expected)
      return false;
  }
  return true;
}
}
}
}
