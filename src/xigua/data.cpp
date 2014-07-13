#include "xigua/data.hpp"

namespace xig {

void data::delete_pointer() {
	switch (type()) {
	case data_type::boolean:
		delete reinterpret_cast<bool*>(data_pointer);
		break;
	case data_type::none:
		break;
	case data_type::integer:
		delete reinterpret_cast<long long*>(data_pointer);
		break;
	case data_type::decimal:
		delete reinterpret_cast<long double*>(data_pointer);
		break;
	case data_type::string:
	case data_type::keyword:
	case data_type::symbol:
		delete reinterpret_cast<std::string*>(data_pointer);
		break;
	case data_type::tuple:
	case data_type::process:
		delete reinterpret_cast<std::vector<data>*>(data_pointer);
		break;
	case data_type::map:
		delete reinterpret_cast<std::map<data, data>*>(data_pointer);
		break;
	case data_type::function:
		delete reinterpret_cast<function*>(data_pointer);
		break;
	case data_type::container:
		delete reinterpret_cast<enviroment*>(data_pointer);
		break;
	}
}


void data::assign_from_other(const data& other) {
	my_type = other.type();
	switch (other.type()) {
	case data_type::boolean:
		data_pointer = new bool(other.as_boolean());
		break;
	case data_type::none:
		data_pointer = nullptr;
		break;
	case data_type::integer:
		data_pointer = new long long(other.as_integer());
		break;
	case data_type::decimal:
		data_pointer = new long double(other.as_decimal());
		break;
	case data_type::string:
	case data_type::keyword:
	case data_type::symbol:
		data_pointer = new std::string(other.as_string());
		break;
	case data_type::tuple:
	case data_type::process:
		data_pointer = new std::vector<data>(other.as_tuple());
		break;
	case data_type::map:
		data_pointer = new std::map<data, data>(other.as_map());
		break;
	case data_type::function:
		data_pointer = new function(other.as_function());
		break;
	case data_type::container:
		data_pointer = new enviroment(*other.as_container());
		break;
	}
}


data::~data() {
	delete_pointer();
}
data::data() {
  my_type = data_type::none;
  data_pointer = nullptr;
}

data::data(const data& other) {
	assign_from_other(other);
}

data::data(long long number) {
  my_type = data_type::integer;
  data_pointer = new long long(number);
}

data::data(long double number) {
  my_type = data_type::decimal;
  data_pointer = new long double(number);
}

data::data(bool boolean_value) {
  my_type = data_type::boolean;
  data_pointer = new bool(boolean_value);
}

data::data(data_type in_type, std::string string_data) {
  my_type = in_type;
  if (in_type == data_type::string || in_type == data_type::symbol ||
      in_type == data_type::keyword) {
    data_pointer = new std::string(string_data);
  } else {
    throw error(error_type::internal_error,
                "Wrong Data Passed to data::data std::string");
  }
}

data::data(data_type in_type, std::vector<data> list_data) {
  my_type = in_type;
  if (in_type == data_type::tuple || in_type == data_type::process) {
    data_pointer = new std::vector<data>(list_data);
  } else if (in_type == data_type::map) {
    std::map<data, data> temp_map;
    for (unsigned int i(0); i + 1 < list_data.size(); i += 2) {
      temp_map[list_data.at(i)] = list_data.at(i + 1);
    }
    data_pointer = new std::map<data, data>(temp_map);
  } else {
    throw error(error_type::internal_error,
                "Wrong Data Passed to data::data std::vector<data>");
  }
}

data::data(std::map<data, data> map_data) {
  my_type = data_type::map;
  data_pointer = new std::map<data, data>(map_data);
}

data::data(function function_data) {
  my_type = data_type::function;
  data_pointer = new function(function_data);
}

data::data(enviroment container_data) {
  my_type = data_type::container;
  data_pointer = new enviroment(container_data);
}


data& data::operator=(const data &other){
	delete_pointer();
	assign_from_other(other);
	return *this;
}


bool data::operator==(const data &other) const {

  if ((type() == data_type::decimal || type() == data_type::integer) &&
      (other.type() == data_type::decimal ||
       other.type() == data_type::integer)) {

    if (type() == data_type::integer && other.type() == data_type::integer) {
      return as_integer() == other.as_integer();
    }
    auto a =
        type() == data_type::decimal ? as_decimal() : (long double)as_integer();
    auto b = other.type() == data_type::decimal
                 ? other.as_decimal()
                 : (long double)other.as_integer();
    return a == b;
  }

  if (type() != other.type())
    return false;

  if (type() == data_type::none)
    return true;

  if (type() == data_type::symbol)
    return (as_symbol() == other.as_symbol());

  if (type() == data_type::boolean)
    return (as_boolean() == other.as_boolean());

  if (type() == data_type::string)
    return (as_string() == other.as_string());

  if (type() == data_type::keyword)
    return (as_keyword() == other.as_keyword());

  if (type() == data_type::decimal)
    return (as_decimal() == other.as_decimal());

  if (type() == data_type::integer)
    return (as_integer() == other.as_integer());

  if (type() == data_type::tuple)
    return (as_tuple() == other.as_tuple());

  if (type() == data_type::map)
    return (as_map() == other.as_map());

  if (type() == data_type::process)
    return false;

  if (type() == data_type::function)
    return false;

  if (type() == data_type::container)
    return false;

  return false;
}

bool data::operator!=(const data &other) const { return !(*this == other); }

bool data::operator<(const data &other) const {
  if (type() != other.type())
    return (type() < other.type());

  if (type() == data_type::none)
    return false;

  if (type() == data_type::symbol)
    return (as_symbol() < other.as_symbol());

  if (type() == data_type::keyword)
    return (as_keyword() < other.as_keyword());

  if (type() == data_type::boolean)
    return (as_boolean() < other.as_boolean());

  if (type() == data_type::string)
    return (as_string() < other.as_string());

  if (type() == data_type::decimal)
    return (as_decimal() < other.as_decimal());

  if (type() == data_type::integer)
    return (as_integer() < other.as_integer());

  if (type() == data_type::tuple)
    return (as_tuple() < other.as_tuple());

  if (type() == data_type::process)
    return false;

  if (type() == data_type::function)
    return false;

  if (type() == data_type::container)
    return false;

  return false;
}

data::operator bool() const {
  if (type() == data_type::boolean)
    return as_boolean();
  else
    throw error(error_type::internal_error, "Invalid cast to bool");
}

data::operator std::string() const {
  if (type() == data_type::string || type() == data_type::symbol ||
      type() == data_type::keyword)
    return as_string();
  else
    throw error(error_type::internal_error, "Invalid cast to bool");
}

data::operator long long() const {
  if (type() == data_type::integer)
    return as_integer();
  else
    throw error(error_type::internal_error, "Invalid cast to long long");
}

data::operator long double() const {
  if (type() == data_type::decimal)
    return as_decimal();
  else
    throw error(error_type::internal_error, "Invalid cast to long double");
}

data::operator std::map<data, data>() const {
  if (type() == data_type::map)
    return as_map();
  else
    throw error(error_type::internal_error, "Invalid cast to map");
}

data::operator function() const {
  if (type() == data_type::function)
    return as_function();
  else
    throw error(error_type::internal_error, "Invalid cast to function");
}

data::operator enviroment *() const {
  if (type() == data_type::container)
    return as_container();
  else
    throw error(error_type::internal_error, "Invalid cast to enviroment");
}

data_type data::type() const { return my_type; }

std::string data::as_string() const {
  return *(static_cast<std::string *>(data_pointer));
}

std::string data::as_keyword() const {
  return *(static_cast<std::string *>(data_pointer));
}

std::string data::as_symbol() const {
  return *(static_cast<std::string *>(data_pointer));
}

long double data::as_decimal() const {
  return *(static_cast<long double *>(data_pointer));
}

long long data::as_integer() const {
  return *(static_cast<long long *>(data_pointer));
}

std::vector<data> data::as_tuple() const {
  return *(static_cast<std::vector<data> *>(data_pointer));
}

std::map<data, data> data::as_map() const {
  return *(static_cast<std::map<data, data> *>(data_pointer));
}

std::vector<data> data::as_process() const {
  return *(static_cast<std::vector<data> *>(data_pointer));
}

bool data::as_boolean() const {
  return *(static_cast<bool *>(data_pointer));
}

function data::as_function() const {
  return *(static_cast<function *>(data_pointer));
}

enviroment *data::as_container() const {
  return (static_cast<enviroment *>(data_pointer));
}

std::string string_representation(const data &in_data) {
  std::string return_value = "";
  if (in_data.type() == data_type::string) {
    return_value += in_data.as_string();
  } else if (in_data.type() == data_type::keyword) {
    return_value += ":" + in_data.as_string();
  } else if (in_data.type() == data_type::symbol) {
    return_value += in_data.as_symbol();
  } else if (in_data.type() == data_type::boolean) {
    if (in_data.as_boolean()) {
      return_value += "true";
    } else {
      return_value += "false";
    }
  } else if (in_data.type() == data_type::decimal) {
    std::stringstream ss;
    ss << std::fixed;
    ss << in_data.as_decimal();
    std::string str = ss.str();
    int s;
    for (s = str.length() - 1; s > 0; s--) {
      if (str[s] == '0')
        str.erase(s, 1);
      else
        break;
    }
    if (str[s] == '.')
      str.erase(s, 1);
    return_value += str;
  } else if (in_data.type() == data_type::integer) {
    return_value += std::to_string(in_data.as_integer());
  } else if (in_data.type() == data_type::tuple) {
    return_value += "{ ";
    for (auto element : in_data.as_tuple()) {
      return_value += string_representation(element);
      return_value += " ";
    }
    return_value += "}";
  } else if (in_data.type() == data_type::map) {
    return_value += "#{ ";
    for (auto &element : in_data.as_map()) {
      return_value += string_representation(element.first);
      return_value += " => ";
      return_value += string_representation(element.second);
      return_value += ", ";
    }
    return_value += "}";
  } else if (in_data.type() == data_type::process) {
    return_value += "[ ";
    for (auto element : in_data.as_process()) {
      return_value += string_representation(element);
      return_value += " ";
    }
    return_value += "]";
  }
  return return_value;
}

data make_decimal(long double num) { return num; }

data make_integer(long long num) { return num; }

data make_string(std::string str) { return data(data_type::string, str); }

data make_symbol(std::string str) { return data(data_type::symbol, str); }

data make_keyword(std::string str) { return data(data_type::keyword, str); }

data make_boolean(bool b) { return b; }

data make_none() { return data(); }

data make_tuple(std::vector<data> tuple) {
  return data(data_type::tuple, tuple);
}

data make_process(std::vector<data> proc) {
  return data(data_type::process, proc);
}

extern data make_map(std::map<data, data> map) { return map; }

extern data make_container(enviroment container) { return container; }

extern data make_container() { return enviroment(env_type::container); }
}
