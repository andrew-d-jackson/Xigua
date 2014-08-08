#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <map>
#include <tuple>
#include <utility>
#include <memory>

#include "xigua/enviroment.hpp"

#include "xigua/error.hpp"

#include "xigua/function.hpp"

namespace xig {

//! Enum for the different kinds of Xigua data types
enum class data_type {

  //! Represents none/nil/nothing, returned by empty function
  none,
  //! Represents the name of a variable, not an actual data type, just used by
  //! interpreter
  symbol,
  //! Represents a true/false value
  boolean,
  //! Represents a string of charicters, can contain spaces/newlines/etc
  string,
  //! Represents a string of charicters, usually one word, can't contain
  //! spaces/newlines/etc, typically used as a key in a map
  keyword,
  //! Represents a floating point number
  integer,
  //! Represents a floating point number
  decimal,
  //! Represents a list containing any number of elements and types, can contain
  //! data of multiple types in the same tuple
  tuple,
  //! Represents a hash map of keys and values, can contain keys/values of
  // multiple types in the same map
  map,
  //! Represents a unexecuted process, not an actual data type, just used by
  //! intepreter
  process,
  //! Represents a function of a single method or multiple overloads
  function,
  //! Represents an enviroment containing variables, not an actual data type,
  //! just used by intepreter
  container
};

class data;
typedef std::shared_ptr<data> data_ptr;

class data {
public:
	virtual ~data() {}

	virtual data_type type() const = 0;

	virtual bool operator<(const data &other) const = 0;
	virtual bool operator==(const data &other) const = 0;
	virtual bool operator!=(const data &other) const {
		return !(*this == other);
	};

	virtual const boolean &as_boolean() const {
		throw;
	}

	virtual const tuple &as_tuple() const {
		throw;
	}

	virtual const integer &as_integer() const {
		throw;
	}

	virtual const decimal &as_decimal() const {
		throw;
	}

	virtual const map &as_map() const {
		throw;
	}

	virtual const string &as_string() const {
		throw;
	}

	virtual const symbol &as_symbol() const {
		throw;
	}

	virtual const keyword &as_keyword() const {
		throw;
	}

	virtual const process &as_process() const {
		throw;
	}

	virtual const none &as_none() const {
		throw;
	}
};

class none : public data {
public:
	virtual ~none() {}

	virtual data_type type() const { return data_type::none; };

	virtual const none &as_none() const {
		return *this;
	}

	virtual bool operator<(const data &other) const {
		if (type() == other.type())
			return false;
		return type() < other.type();
	}

	virtual bool operator==(const data &other) const {
		if (type() == other.type())
			return true;
		return false;
	}
};

class boolean : public data {
private:
	bool value;
public:
	boolean(bool value) : value(value) {}
	virtual ~boolean() {}

	virtual data_type type() const { return data_type::boolean; };

	virtual const boolean &as_boolean() const {
		return *this;
	}

	operator bool() const { return value; }
	bool as_bool() const { return value; }

	virtual bool operator<(const data &other) const {
		if (type() == other.type())
			return (value < other.as_boolean().value);
		return type() < other.type();
	}

	virtual bool operator==(const data &other) const {
		if (type() == other.type())
			return (value == other.as_boolean().value);
		return false;
	}
};

class integer : public data {
private:
	long long value;
public:
	integer(long long value) : value(value) {}
	virtual ~integer() {}

	virtual data_type type() const { return data_type::integer; };

	virtual const integer &as_integer() const {
		return *this;
	}

	operator int() const { return value; }
	long long as_int() const { return value; }

	virtual bool operator<(const data &other) const {
		if (type() == other.type())
			return (value < other.as_integer().value);
		return type() < other.type();
	}

	virtual bool operator==(const data &other) const {
		if (type() == other.type())
			return (value == other.as_integer().value);
		return false;
	}
};

class decimal : public data {
private:
	long double value;
public:
	decimal(long double value) : value(value) {}
	virtual ~decimal() {}

	virtual data_type type() const { return data_type::decimal; };

	virtual const decimal &as_decimal() const {
		return *this;
	}

	operator double() const { return value; }
	long double as_double() const { return value; }

	virtual bool operator<(const data &other) const {
		if (type() == other.type())
			return (value < other.as_decimal().value);
		return type() < other.type();
	}

	virtual bool operator==(const data &other) const {
		if (type() == other.type())
			return (value == other.as_decimal().value);
		return false;
	}
};

class string : public data {
private:
	std::string value;
public:
	string(std::string value) : value(value) {}
	virtual ~string() {}

	virtual data_type type() const { return data_type::string; };

	virtual const string &as_string() const {
		return *this;
	}

	operator std::string() const { return value; }
	std::string as_std_string() const { return value; }

	virtual bool operator<(const data &other) const {
		if (type() == other.type())
			return (value < other.as_string().value);
		return type() < other.type();
	}

	virtual bool operator==(const data &other) const {
		if (type() == other.type())
			return (value == other.as_string().value);
		return false;
	}
};

class symbol : public data {
private:
	std::string value;
public:
	symbol(std::string value) : value(value) {}
	virtual ~symbol() {}

	virtual data_type type() const { return data_type::symbol; };

	virtual const symbol &as_symbol() const {
		return *this;
	}

	operator std::string() const { return value; }
	std::string as_std_string() const { return value; }

	virtual bool operator<(const data &other) const {
		if (type() == other.type())
			return (value < other.as_symbol().value);
		return type() < other.type();
	}

	virtual bool operator==(const data &other) const {
		if (type() == other.type())
			return (value == other.as_symbol().value);
		return false;
	}
};

class keyword : public data {
private:
	std::string value;
public:
	keyword(std::string value) : value(value) {}
	virtual ~keyword() {}

	virtual data_type type() const { return data_type::keyword; };

	virtual const keyword &as_keyword() const {
		return *this;
	}

	operator std::string() const { return value; }
	std::string as_std_string() const { return value; }

	virtual bool operator<(const data &other) const {
		if (type() == other.type())
			return (value < other.as_keyword().value);
		return type() < other.type();
	}

	virtual bool operator==(const data &other) const {
		if (type() == other.type())
			return (value == other.as_keyword().value);
		return false;
	}
};

class map : public data {
private:
	std::map<data_ptr, data_ptr> value;
public:
	map(std::map<data_ptr, data_ptr> value) : value(value) {}
	virtual ~map() {}

	virtual data_type type() const { return data_type::map; };

	virtual const map &as_map() const {
		return *this;
	}

	operator std::map<data_ptr, data_ptr>() const { return value; }
	std::map<data_ptr, data_ptr> as_std_map() const { return value; }

	virtual bool operator<(const data &other) const {
		if (type() == other.type())
			return (value < other.as_map().value);
		return type() < other.type();
	}

	virtual bool operator==(const data &other) const {
		if (type() == other.type())
			return (value == other.as_map().value);
		return false;
	}
};

class tuple : public data {
private:
	std::vector<data_ptr> value;
public:
	tuple(std::vector<data_ptr> value) : value(value) {}
	virtual ~tuple() {}

	virtual data_type type() const { return data_type::tuple; };

	virtual const tuple &as_tuple() const {
		return *this;
	}

	operator std::vector<data_ptr>() const { return value; }
	std::vector<data_ptr> as_std_vector() const { return value; }

	virtual bool operator<(const data &other) const {
		if (type() == other.type())
			return (value < other.as_tuple().value);
		return type() < other.type();
	}

	virtual bool operator==(const data &other) const {
		if (type() == other.type())
			return (value == other.as_tuple().value);
		return false;
	}
};

class process : public data {
private:
	std::vector<data_ptr> value;
public:
	process(std::vector<data_ptr> value) : value(value) {}
	virtual ~process() {}

	virtual data_type type() const { return data_type::process; };

	virtual const process &as_process() const {
		return *this;
	}

	operator std::vector<data_ptr>() const { return value; }
	std::vector<data_ptr> as_std_vector() const { return value; }

	virtual bool operator<(const data &other) const {
		if (type() == other.type())
			return (value < other.as_process().value);
		return type() < other.type();
	}

	virtual bool operator==(const data &other) const {
		if (type() == other.type())
			return (value == other.as_process().value);
		return false;
	}
};

extern std::string string_representation(const data &in_data);

//! Helper function to make data of type number
extern data_ptr make_decimal(long double num) {
	return std::make_shared<decimal>(num);
}

//! Helper function to make data of type number
extern data_ptr make_integer(long long num) {
	return std::make_shared<integer>(num);
}

//! Helper function to make data of type string
extern data_ptr make_string(std::string str) {
	return std::make_shared<string>(str);
}

//! Helper function to make data of type symbol
extern data_ptr make_symbol(std::string str) {
	return std::make_shared<symbol>(str);
}

//! Helper function to make data of type keyword
extern data_ptr make_keyword(std::string str) {
	return std::make_shared<keyword>(str);
}

//! Helper function to make data of type boolean
extern data_ptr make_boolean(bool b) {
	return std::make_shared<boolean>(b);
}

//! Helper function to make data of type none
extern data_ptr make_none() {
	return std::make_shared<none>();
}

//! Helper function to make data of type tuple
extern data_ptr make_tuple(std::vector<data> val) {
	return std::make_shared<tuple>(val);
}

//! Helper function to make data of type process
extern data_ptr make_process(std::vector<data> val) {
	return std::make_shared<process>(val);
}

//! Helper function to make data of type map
extern data_ptr make_map(std::map<data, data> val) {
	return std::make_shared<map>(val);
}

//! Helper function to make data of type container from an enviroment
//extern data_ptr make_container(enviroment container);

//! Helper function to make data of type blank container
//extern data_ptr make_container();

//! Helper function to make data of type function
//template <typename T> extern data_ptr make_function(T fn) { return function(fn); }
}
