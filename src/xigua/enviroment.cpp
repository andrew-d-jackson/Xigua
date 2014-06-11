#include "xigua/enviroment.hpp"

namespace xig {

enviroment::enviroment(env_type in_type) {
  type(in_type);
  my_relative_path = "";
  my_parent = nullptr;
}

enviroment::enviroment(env_type in_type, enviroment *parent_enviroment) {
  type(in_type);
  my_relative_path = "";

  if (in_type != env_type::container) {
    if (parent_enviroment->type() != env_type::container) {
      defined_variables = (*parent_enviroment).defined_variables;
      my_parent = parent_enviroment->parent();
    } else {
      my_parent = parent_enviroment;
    }
  } else {
    my_parent = parent_enviroment;
  }
}

void enviroment::type(env_type in_type) {
  my_type = in_type;
};

env_type enviroment::type() const {
  return my_type;
};

data *enviroment::find(std::string variable_name, bool this_only) {
  std::string delimiter = "::";
  size_t pos = 0;
  if ((pos = variable_name.find(delimiter)) != std::string::npos) {

    auto var_env = variable_name.substr(0, pos);
    auto new_var_name = variable_name;
    new_var_name.erase(0, pos + delimiter.length());

    auto e = find(var_env);
    if (e == nullptr || e->type() != data_type::container) {
      if (parent() != nullptr && !this_only) {
        auto data = parent()->find(variable_name);
        return data;
      }
      return nullptr;
    }
    return e->as_container()->find(new_var_name);
  }

  if (defined_variables.find(variable_name) != defined_variables.end())
    return &defined_variables[variable_name];

  if (parent() != nullptr && !this_only) {
    auto data = parent()->find(variable_name);
    return data;
  }

  return nullptr;
}

void enviroment::set(std::string name, data value, bool force_here) {
  if (force_here) {
    defined_variables[name] = value;
  } else if (my_type == env_type::container || my_type == env_type::function) {
    defined_variables[name] = value;
  } else if (my_type == env_type::macro || my_type == env_type::let) {
    parent()->set(name, value);
  }
}

enviroment *enviroment::parent() const {
  return my_parent;
};

bool enviroment::has_parent() const { return (parent() != nullptr); }

std::string enviroment::relative_path() const {
  if (has_parent() && (my_relative_path == "")) {
    return parent()->relative_path();
  }
  return my_relative_path;
}

void enviroment::set_relative_path(std::string path) {
  my_relative_path = path;
}
}
