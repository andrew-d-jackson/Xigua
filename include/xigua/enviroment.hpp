#pragma once

#include <string>
#include <map>

#include "xigua/data.hpp"
#include "xigua/types.hpp"

namespace xig {
class data;

//! Enum for the different kinds of Xigua enviroment types
enum class env_type { container, function, macro, let };

//! Class that holds Xigua variables
class enviroment : public data {
public:
  //! Construct Enviroment with no parent
  enviroment(env_type in_type);
  //! Construct Enviroment with parent
  enviroment(env_type in_type, enviroment *parent);

  virtual ~enviroment() {}

  virtual data_type type() const { return data_type::enviroment; }
  virtual const enviroment &as_enviroment() const { return *this; }
  virtual bool operator<(const data &other) const {
    if (type() == other.type())
      return defined_variables < other.as_enviroment().defined_variables;
    return type() < other.type();
  }

  virtual bool operator==(const data &other) const {
    if (type() == other.type())
      return defined_variables == other.as_enviroment().defined_variables;
    return false;
  }

  //! Get the type of this enviroment
  env_type enviroment_type() const;
  //! Set the type of this enviroment
  void type(env_type in_type);

  //! Find a variable in this enviroment, returns a pointer to the a data object
  //! of the variable if found, returns nullptr if not, if this_only is set to
  //! true does not search parents
  data_ptr find(std::string variable_name, bool this_only = false) const;

  //! Insert a variable into the enviroment, force_here forces the variable to
  //! be in this enviroment even if the type of enviroment would rather put it
  //! in the enviroments parent
  void set(std::string name, data_ptr value, bool force_here = false);

  //! Get the enviroments parent
  enviroment *parent() const;
  //! Check if this enviroment has a parent
  bool has_parent() const;

  //! Get the relative path of the file the enviroment was created with
  std::string relative_path() const;
  //! Set the relative path
  void set_relative_path(std::string path);

  void print_all_vars();

private:
  std::map<std::string, data_ptr> defined_variables;
  enviroment *my_parent;
  env_type my_type;
  std::string my_relative_path;
};
}
