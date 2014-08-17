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

static std::string delimiter = "::";

data_ptr find_with_delimiter(const enviroment &me, const std::map<std::string, data_ptr> &defined_variables,  const std::string &variable_name) {
	auto delimiter_position = variable_name.find(delimiter);
	if (delimiter_position != std::string::npos) {
		auto env_name = variable_name.substr(delimiter_position + delimiter.length());
		auto var_name = variable_name.substr(0, delimiter_position);
		auto env = me.find(env_name);
		if (env && env->type() == data_type::enviroment) {
			return env->as_enviroment().find(var_name);
		} 
		return data_ptr(nullptr);
	}
	return data_ptr(nullptr);
}

data_ptr find_in_map(const std::map<std::string, data_ptr> &defined_variables, const std::string &variable_name) {
	auto found = defined_variables.find(variable_name);
	if (found != defined_variables.end())
		return found->second;
	return data_ptr(nullptr);
}

data_ptr find_in_parent(const enviroment &me, const std::string &variable_name) {
	if (me.has_parent()) {
		return me.parent()->find(variable_name);
	}
}

data_ptr enviroment::find(std::string variable_name) const {
	auto found_delimiter = variable_name.find(delimiter);
	if (found_delimiter != std::string::npos) {
		auto found_var = find_with_delimiter(*this, defined_variables, variable_name);
		if (found_var)
			return found_var;
		parent()->find(variable_name);
	}

	auto found_in_me = find_in_map(defined_variables, variable_name);
	if (found_in_me)
		return found_in_me;

	return find_in_parent(*this, variable_name);
}

data_ptr enviroment::find_here(std::string variable_name) const {
	auto found_delimiter = variable_name.find(delimiter);
	if (found_delimiter != std::string::npos) {
		return find_with_delimiter(*this, defined_variables, variable_name);
	}

	return find_in_map(defined_variables, variable_name);
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
