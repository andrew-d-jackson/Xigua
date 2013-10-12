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

namespace xig
{

	enum class data_type { None, Symbol, Bool, String, Number, Tuple, HashMap, Proc, Function };

	class data;
	class Enviroment;

	typedef std::function<data(std::vector<data>, Enviroment*, std::vector<std::string>)> xigua_lambda_t;

	class data
	{
	protected:
		data_type my_type;
		typedef std::map<std::pair<int, int>, std::tuple<xigua_lambda_t, bool>> function_map_t;
		std::shared_ptr<void> data_pointer;

	public:
		data(){}
		data(data_type in_type);
		data(data_type in_type, std::string string_data);
		data(data_type in_type, long double number_data);
		data(data_type in_type, bool boolean_data);
		data(data_type in_type, std::vector<data> list_data);
		data(data_type in_type, std::map<data, data> map_data);

		bool operator==(const data & other) const;
		bool operator!=(const data & other) const;
		bool operator<(const data & other) const;

		data_type type() const;
		void type(data_type in_type);

		std::string string() const;
		void string(std::string in_string);
		std::string as_string() const;

		std::string symbol() const;
		void symbol(std::string symbol_name);

		long double number() const;
		void number(long double in_number);

		std::vector<data> tuple() const;
		void tuple(std::vector<data> in_tuple);

		std::map<data, data> hash_map() const;
		void hash_map(std::map<data, data> in_map);
		void hash_map(std::vector<data> in_list);

		std::vector<data> proc() const;
		void proc(std::vector<data> in_list);

		bool boolean() const;
		void boolean(bool boolean);

		function_map_t function_map() const;
		void function_map(function_map_t in_fmap);

		void set_function(xigua_lambda_t func, int num_args, int repeating_args, bool should_eval);
		data call_function(std::vector<data> & args, Enviroment * enviroment, std::vector<std::string> function_call_list);
		data evaluate(Enviroment * enviroment, std::vector<std::string> function_call_list = std::vector<std::string>());
		void print(int indentation = 0);
	};

}
