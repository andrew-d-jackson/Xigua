#include "xigua/enviroment.hpp"

namespace xig {

enviroment::enviroment(env_type in_type) {
  my_type = in_type;
  my_relative_path = "";
  my_parent = nullptr;
}

enviroment::enviroment(env_type in_type, enviroment *parent_enviroment) {
  my_type = in_type;
  my_relative_path = "";

  if (in_type != env_type::container) {
    if (parent_enviroment->enviroment_type() != env_type::container) {
      defined_variables = (*parent_enviroment).defined_variables;
      my_parent = parent_enviroment->parent();
    } else {
      my_parent = parent_enviroment;
    }
  } else {
    my_parent = parent_enviroment;
  }
}

data_type enviroment::type() const { return data_type::enviroment; }

const enviroment &enviroment::as_enviroment() const { return *this; }

env_type enviroment::enviroment_type() const {
  return my_type;
};


data_ptr enviroment::find_here(std::string variable_name) const {
	auto found_position = defined_variables.find(variable_name);
	if (found_position != defined_variables.end())
		return found_position->second;
}

data_ptr enviroment::find(std::string variable_name) const {
  std::string delimiter = "::";
  size_t pos = 0;
  if ((pos = variable_name.find(delimiter)) != std::string::npos) {

    auto var_env = variable_name.substr(0, pos);
    auto new_var_name = variable_name;
    new_var_name.erase(0, pos + delimiter.length());

    auto e = find(var_env);
    if (!e || e->type() != data_type::enviroment) {
      if (parent() != nullptr) {
        auto data = parent()->find(variable_name);
        return data;
      }
      return data_ptr(nullptr);
    }
	return e->as_enviroment().find(new_var_name);
  }

  if (defined_variables.find(variable_name) != defined_variables.end())
	  return defined_variables.find(variable_name)->second;

  if (parent() != nullptr) {
    auto data = parent()->find(variable_name);
    return data;
  }

  return data_ptr(nullptr);
  ;
}

void enviroment::set(std::string name, data_ptr value) {
	if (my_type == env_type::container || my_type == env_type::function) {
		defined_variables[name] = value;
	}
	else if (my_type == env_type::macro || my_type == env_type::let) {
		parent()->set(name, value);
	}
}

void enviroment::set_here(std::string name, data_ptr value) {
	defined_variables[name] = value;
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

void enviroment::print_all_vars() {
  std::cout << " -------------------- " << std::endl;
  for (auto i : defined_variables) {
    std::cout << i.first << "  =>  " << string_representation(i.second)
              << std::endl;
  }
  std::cout << " -------------------- " << std::endl;
}

bool enviroment::operator<(const data &other) const {
	if (type() == other.type())
		return defined_variables < other.as_enviroment().defined_variables;
	return type() < other.type();
}

bool enviroment::operator==(const data &other) const {
	if (type() == other.type())
		return defined_variables == other.as_enviroment().defined_variables;
	return false;
}

}
