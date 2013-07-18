#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <tuple>

#include "enviroment.hpp"

namespace Xigua
{
	enum class DataTypes { None, Symbol, Bool, String, Number, Tuple, Proc, Function };

	class DataType;
	class Enviroment;

	typedef std::function<DataType(std::vector<DataType>, Enviroment*)> xigua_lambda_t;

	class DataType
	{
	public:
		DataTypes type;
		std::string string;
		long double number;
		bool boolean;
		std::vector<DataType> list;
		std::map <int, std::tuple<xigua_lambda_t, int, bool>> func_map; // args : func, repeating, sould eval


		DataType(){}
		DataType(DataTypes data_type);
		DataType(DataTypes data_type, std::string string_data);
		DataType(DataTypes data_type, long double number_data);
		DataType(DataTypes data_type, bool boolean_data);

		void set_function(xigua_lambda_t func, int num_args, int repeating_args, bool should_eval);
		DataType call_function(std::vector<DataType> & args, Enviroment * enviroment);
		DataType evaluate(Enviroment * enviroment);
		void print(int indentation);
	};
}