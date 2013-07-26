#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <tuple>
#include <utility>

#include "enviroment.hpp"


namespace Xigua
{

	enum class DataTypes { None, Symbol, Bool, String, Number, Tuple, Proc, Function };

	class DataType;
	class Enviroment;

	typedef std::function<DataType(std::vector<DataType>, Enviroment*)> xigua_lambda_t;

	class DataType
	{
	protected:
		DataTypes d_type;
		std::string d_string;
		long double d_number;
		bool d_boolean;
		std::vector<DataType> d_list;
		std::map <std::pair<int, int>, std::tuple<xigua_lambda_t, bool>> d_func_map; // args repeating : func, sould eval

	public:
		DataType(){}
		DataType(DataTypes data_type);
		DataType(DataTypes data_type, std::string string_data);
		DataType(DataTypes data_type, long double number_data);
		DataType(DataTypes data_type, bool boolean_data);
		DataType(DataTypes data_type, std::vector<DataType> list_data);

		DataTypes type() const;
		void type(DataTypes in_type);

		std::string string() const;
		void string(std::string in_string);

		std::string symbol() const;
		void symbol(std::string symbol_name);

		long double number() const;
		void number(long double in_number);

		std::vector<DataType> tuple() const;
		void tuple(std::vector<DataType> in_tuple);

		std::vector<DataType> proc() const;
		void proc(std::vector<DataType> in_list);
		void proc_push_back(DataType item);

		bool boolean() const;
		void boolean(bool boolean);

		void set_function(xigua_lambda_t func, int num_args, int repeating_args, bool should_eval);
		DataType call_function(std::vector<DataType> & args, Enviroment * enviroment);
		DataType evaluate(Enviroment * enviroment);
		void print(int indentation = 0);
	};

}
