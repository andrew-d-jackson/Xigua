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

	enum class data_type { none, symbol, boolean, string, keyword, number, tuple, map, process, function, container };

	class data;
	class enviroment;


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

		data_type type() const;

		std::string as_string() const;
		std::string as_symbol() const;
		std::string as_keyword() const;
		long double as_number() const;
		std::vector<data> as_tuple() const;
		std::map<data, data> as_map() const;
		std::vector<data> as_process() const;
		bool as_boolean() const;
		function as_function() const;
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

	extern std::string string_representation(const data & in_data);

	extern data make_number(long double num);
	extern data make_string(std::string str);
	extern data make_keyword(std::string str);
	extern data make_boolean(bool b);
	extern data make_tuple(std::vector<data> tuple);
	extern data make_process(std::vector<data> proc);
	extern data make_map(std::map<data, data> map);
	extern data make_container(enviroment container);
	extern data make_container();

	template<typename T>
	extern data make_function(T fn) {
		return data(data_type::function, function(fn));
	}


}
