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

#include "enviroment.hpp"

#include "error.hpp"

#include "function.hpp"

namespace xig
{

	enum class data_type { none, symbol, boolean, string, number, tuple, map, process, function };

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

		bool operator==(const data & other) const;
		bool operator!=(const data & other) const;
		bool operator<(const data & other) const;

		data_type type() const;

		std::string string() const;
		std::string symbol() const;
		long double number() const;
		std::vector<data> tuple() const;
		std::map<data, data> hash_map() const;
		std::vector<data> proc() const;
		bool boolean() const;
		function functions() const;

		std::string as_string() const;

	protected:
		void type(data_type in_type);

		void string(std::string in_string);
		void symbol(std::string symbol_name);
		void number(long double in_number);
		void boolean(bool boolean);
		void tuple(std::vector<data> in_tuple);
		void hash_map(std::map<data, data> in_map);
		void hash_map(std::vector<data> in_list);
		void proc(std::vector<data> in_list);
		void functions(function in_function);
	};

}
