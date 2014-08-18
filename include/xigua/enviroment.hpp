#pragma once

#include <string>
#include <map>

#include "xigua/data.hpp"
#include "xigua/types.hpp"

namespace xig {

enum class env_type { container, function, macro, let };

class enviroment : public data {
public:
  enviroment(env_type in_type);
  enviroment(env_type in_type, enviroment *parent);

  virtual ~enviroment() {}

  virtual data_type type() const;
  virtual const enviroment &as_enviroment() const;
  virtual bool operator<(const data &other) const;
  virtual bool operator==(const data &other) const;

  env_type enviroment_type() const;

  data_ptr find(std::string variable_name) const;
  data_ptr find_here(std::string variable_name) const;

  void set(std::string name, data_ptr value);
  void set_here(std::string name, data_ptr value);

  enviroment *parent() const;
  bool has_parent() const;

  std::string relative_path() const;
  void set_relative_path(std::string path);

  void print_all_vars();

private:
  std::map<std::string, data_ptr> defined_variables;
  enviroment *my_parent;
  env_type my_type;
  std::string my_relative_path;
};
}
