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

namespace xig
{

	//! Enum for the different kinds of Xigua data types
	enum class data_type { none, symbol, boolean, string, keyword, number, tuple, map, process, function, container };

	class data;
	class enviroment;

	//! Generic class that holds all Xigua data types
	class data
	{
	protected:
		data_type my_type;
		std::shared_ptr<void> data_pointer;

	public:
		data(){}
		data(data_type in_type);
		data(data_type in_type, std::string string_data);
		data(data_type in_type, long double number_data);
		data(data_type in_type, bool boolean_data);
		data(data_type in_type, std::vector<data> list_data);
		data(data_type in_type, std::map<data, data> map_data);
		data(data_type in_type, function function_data);
		data(data_type in_type, enviroment container_data);

		bool operator==(const data & other) const;
		bool operator!=(const data & other) const;
		bool operator<(const data & other) const;

		//! Get the type of the data
		data_type type() const;

		//! Get a copy data as a std::string, assumes type is string 
		std::string as_string() const;
		//! Get a copy data as a std::string, assumes type is symbol 
		std::string as_symbol() const;
		//! Get a copy data as a std::string, assumes type is keyword, won't include : 
		std::string as_keyword() const;
		//! Get a copy data as a long double, assumes type is number 
		long double as_number() const;
		//! Get a copy data as a std::vector of data, assumes type is tuple 
		std::vector<data> as_tuple() const;
		//! Get a copy data as a std::map of data as the key and the value, assumes type is map 
		std::map<data, data> as_map() const;
		//! Get a copy data as a std::vector of data, assumes type is process 
		std::vector<data> as_process() const;
		//! Get a copy data as a bool, assumes type is boolean 
		bool as_boolean() const;
		//! Get a copy data as a function, assumes type is function 
		function as_function() const;
		//! Get a copy data as an enviroment pointer, assumes type is container 
		enviroment* as_container() const;

	protected:
		void type(data_type in_type);

		void string(std::string in_string);
		void symbol(std::string symbol_name);
		void keyword(std::string keyword_name);
		void number(long double in_number);
		void boolean(bool boolean);
		void tuple(std::vector<data> in_tuple);
		void hash_map(std::map<data, data> in_map);
		void hash_map(std::vector<data> in_list);
		void proc(std::vector<data> in_list);
		void functions(function in_function);
		void container(enviroment in_container);
	};

	//! Get a nice string representation of a piece of data
	extern std::string string_representation(const data & in_data);

	//! Helpter function to make data of type number
	extern data make_number(long double num);
	//! Helpter function to make data of type string
	extern data make_string(std::string str);
	//! Helpter function to make data of type symbol
	extern data make_symbol(std::string str);
	//! Helpter function to make data of type keyword
	extern data make_keyword(std::string str);
	//! Helpter function to make data of type boolean
	extern data make_boolean(bool b);
	//! Helpter function to make data of type tuple
	extern data make_tuple(std::vector<data> tuple);
	//! Helpter function to make data of type process
	extern data make_process(std::vector<data> proc);
	//! Helpter function to make data of type map
	extern data make_map(std::map<data, data> map);
	//! Helpter function to make data of type container from an enviroment
	extern data make_container(enviroment container);
	//! Helpter function to make data of type blank container
	extern data make_container();

	//! Helpter function to make data of type function
	template<typename T>
	extern data make_function(T fn) {
		return data(data_type::function, function(fn));
	}


}
