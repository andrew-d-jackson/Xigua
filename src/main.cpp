#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <map>
#include <tuple>
#include <limits>
#include <regex>

enum DataTypes { None, Symbol, Bool, String, Number, Tuple, Proc, Function };

class Enviroment;
class DataType;
class FunctionContainer;
DataType eval(DataType data, Enviroment* enviroment);
void print_data(DataType data, int indentation = 0);

typedef std::function<DataType(std::vector<DataType>, Enviroment*)> kiwi_func;

class DataType
{
public:
	DataTypes type;
	std::string string;
	long double number;
	bool boolean;
	std::vector<DataType> list;
	std::map < int, std::tuple<kiwi_func, int, bool> > func_map; // args : func, repeating, sould eval
	//Enviroment enviroment;

	DataType(DataTypes in_type)
	{
		type = in_type;
	}

	DataType(){}

	void set_function(kiwi_func func, int amount_of_args, int repeating_args, bool should_eval)
	{
		func_map[amount_of_args] = std::make_tuple(func, repeating_args, should_eval);
	}

	DataType call_function(std::vector<DataType> & args, Enviroment* enviroment)
	{
		int args_size = args.size();
		auto finder = func_map.find(args_size);

		if (finder == func_map.end())
		{
			std::cout << "Wrong amount of args passed to function";
			exit(1);
		}

		if (std::get<2>(func_map[args_size])) //should eval
		{
			for (auto & item : args)
			{
				if (item.type == Proc || item.type == Symbol)
					item = eval(item, enviroment);
			}
		}

		return std::get<0>(func_map[args_size])(args, enviroment);
	}
};

class Enviroment
{
public:
	std::map<std::string, DataType> defined_variables;
	Enviroment* parent_eviroment;// = nullptr;

	DataType* find(std::string variable_name) {
		if (defined_variables.find(variable_name) != defined_variables.end())
			return &defined_variables[variable_name];

		if (parent_eviroment != nullptr)
		{
			auto data = parent_eviroment->find(variable_name);
			return data;
		}

		return nullptr;
	}

	void set(std::string name, DataType value)
	{
		defined_variables[name] = value;
	}

	Enviroment() : parent_eviroment(nullptr){}
	Enviroment(Enviroment * parent) : parent_eviroment(parent){}
};


DataType eval(DataType data, Enviroment* enviroment)
{
	if (data.type == Symbol)
	{
		DataType* symbol_value = enviroment->find(data.string);
		if (symbol_value == nullptr)
		{
			std::cout << "Cannot Find Symbol: " << data.string << std::endl;
			exit(1);
		}
		return *symbol_value;
	}
	else if (data.type == Number)
	{
		return data;
	}
	else if (data.type == String)
	{
		return data;
	}
	else if (data.type == Bool)
	{
		return data;
	}
	else if (data.type == Proc)
	{
		if (data.list.size() == 0)
		{
			return DataType(None);
		}
		else if (data.list.at(0).type == Symbol)
		{
			auto firstElement = data.list.begin() + 1;
			auto lastElement = data.list.end();
			std::vector<DataType> functionArgs(firstElement, lastElement);

			return eval(data.list.at(0), enviroment).call_function(functionArgs, enviroment);
		}
		else
		{
			for (DataType item : data.list)
				eval(item, enviroment);
		}
	}

	return DataType(None);

}

DataType func_less_than(std::vector<DataType> inputs, Enviroment* enviroment)
{
	DataType return_data(Bool);
	return_data.boolean = true;

	long double previous_num = std::numeric_limits<long double>::max();

	for (const auto & input : inputs)
	{
		if (input.type != Number)
		{
			std::cout << "Not a Number";
			exit(1);
		}

		if (input.number < previous_num)
		{
			previous_num = input.number;
		}
		else
		{
			return_data.boolean = false;
		}
	}

	return return_data;
}

DataType func_greater_than(std::vector<DataType> inputs, Enviroment* enviroment)
{
	DataType return_data(Bool);
	return_data.boolean = true;

	long double previous_num = std::numeric_limits<long double>::min();

	for (const auto & input : inputs)
	{
		if (input.type != Number)
		{
			std::cout << "Not a Number";
			exit(1);
		}

		if (input.number > previous_num)
		{
			previous_num = input.number;
		}
		else
		{
			return_data.boolean = false;
		}
	}

	return return_data;
}

DataType func_equals(std::vector<DataType> inputs, Enviroment* enviroment)
{
	DataType return_data(Bool);
	return_data.boolean = true;

	long double previous_num = inputs.at(0).number;

	for (const auto & input : inputs)
	{
		if (input.type != Number)
		{
			std::cout << "Not a Number";
			exit(1);
		}

		if (input.number == previous_num)
		{
			previous_num = input.number;
		}
		else
		{
			return_data.boolean = false;
		}
	}

	return return_data;
}

DataType func_add(std::vector<DataType> inputs, Enviroment* enviroment)
{
	DataType return_data(Number);
	return_data.number = 0;

	for (const auto & input : inputs)
	{
		if (input.type != Number)
		{
			std::cout << "Not a Number";
			exit(1);
		}
		return_data.number = return_data.number + input.number;
	}

	return return_data;
}

DataType func_minus(std::vector<DataType> inputs, Enviroment* enviroment)
{
	DataType return_data(Number);
	return_data.number = inputs.at(0).number * 2;

	for (const auto & input : inputs)
	{
		if (input.type != Number)
		{
			std::cout << "Not a Number";
			exit(1);
		}
		return_data.number = return_data.number - input.number;
	}

	return return_data;
}

DataType func_multiply(std::vector<DataType> inputs, Enviroment* enviroment)
{
	DataType return_data(Number);
	return_data.number = inputs.at(0).number * inputs.at(1).number;
	return return_data;
}

DataType func_divide(std::vector<DataType> inputs, Enviroment* enviroment)
{
	DataType return_data(Number);
	return_data.number = inputs.at(0).number / inputs.at(1).number;
	return return_data;
}

DataType func_concatinate_strings(std::vector<DataType> inputs, Enviroment* enviroment)
{
	DataType return_data(String);
	return_data.string = inputs.at(0).string + inputs.at(1).string;
	return return_data;
}

DataType func_uppercase_string(std::vector<DataType> inputs, Enviroment* enviroment)
{
	DataType return_data(String);
	return_data.string = inputs.at(0).string;
	return return_data;
}

DataType func_print_line(std::vector<DataType> inputs, Enviroment* enviroment)
{
	if (inputs.at(0).type == String)
		std::cout << inputs.at(0).string << std::endl;
	else if (inputs.at(0).type == Number)
		std::cout << inputs.at(0).number << std::endl;
	else if (inputs.at(0).type == Bool)
		if (inputs.at(0).boolean)
			std::cout << "true" << std::endl;
		else
			std::cout << "false" << std::endl;


	return DataType(None);
}

DataType func_if(std::vector<DataType> inputs, Enviroment* enviroment)
{
	if (eval(inputs.at(0), enviroment).boolean)
		return eval(inputs.at(1), enviroment);
	else
		return eval(inputs.at(2), enviroment);
}

DataType func_define(std::vector<DataType> inputs, Enviroment* enviroment)
{
	enviroment->set(inputs.at(0).string, eval(inputs.at(1), enviroment));
	return DataType(None);
}

DataType func_lambda(std::vector<DataType> inputs, Enviroment* enviroment)
{
	Enviroment nenv(enviroment);
	DataType return_data(Function);

	kiwi_func fn = [nenv, inputs](std::vector<DataType> fn_inputs, Enviroment* fn_enviroment)mutable->DataType
	{
		for (unsigned int i(0); i < fn_inputs.size(); i++)
		{
			nenv.set(inputs.at(0).list.at(i).string, fn_inputs.at(i));
		}

		return eval(inputs.at(1), &nenv);
	};

	return_data.set_function(fn, inputs.at(0).list.size(), 0, true);

	return return_data;
}

Enviroment get_global_enviroment()
{
	Enviroment enviroment;

	enviroment.defined_variables["+"] = DataType(Function);
	enviroment.defined_variables["+"].set_function(&func_add, 2, 0, true);

	enviroment.defined_variables["-"] = DataType(Function);
	enviroment.defined_variables["-"].set_function(&func_minus, 2, 0, true);

	//	enviroment.defined_variables["-"] = lambda_generator(&func_minus, { Number, Number });
	//	enviroment.defined_variables["*"] = lambda_generator(&func_multiply, { Number, Number });
	//	enviroment.defined_variables["/"] = lambda_generator(&func_divide, { Number, Number });
	//	enviroment.defined_variables["<"] = lambda_generator(&func_less_than, { Number, Number });
	//	enviroment.defined_variables[">"] = lambda_generator(&func_greater_than, { Number, Number });

	enviroment.defined_variables["=="] = DataType(Function);
	enviroment.defined_variables["=="].set_function(&func_equals, 2, 0, true);

	enviroment.defined_variables["conc"] = DataType(Function);
	enviroment.defined_variables["conc"].set_function(&func_concatinate_strings, 2, 0, true);

	enviroment.defined_variables["println"] = DataType(Function);
	enviroment.defined_variables["println"].set_function(&func_print_line, 1, 0, true);

	enviroment.defined_variables["if"] = DataType(Function);
	enviroment.defined_variables["if"].set_function(&func_if, 3, 0, false);

	enviroment.defined_variables["="] = DataType(Function);
	enviroment.defined_variables["="].set_function(&func_define, 2, 0, false);

	enviroment.defined_variables["fn"] = DataType(Function);
	enviroment.defined_variables["fn"].set_function(&func_lambda, 2, 0, false);

	return enviroment;

}

std::vector<std::string> parse_to_string(std::string unparsed_string)
{
	std::vector<std::string> parsed_list;

	bool is_reading_string = false;
	std::stringstream string_buffer;
	bool string_buffer_contains_data = false;
	for (char c : unparsed_string)
	{
		if (c == '[' || c == ']' || c == '{' || c == '}'){

			if (string_buffer_contains_data) {
				parsed_list.push_back(string_buffer.str());
				string_buffer.str("");
				string_buffer_contains_data = false;
			}

			parsed_list.push_back(std::string(1, c));

		}
		else if (c == ' ') {

			if (!is_reading_string) {
				if (string_buffer_contains_data) {
					parsed_list.push_back(string_buffer.str());
					string_buffer.str("");
					string_buffer_contains_data = false;
				}
			}
			else {
				string_buffer << c;
				string_buffer_contains_data = true;
			}

		}
		else if (c == '"') {
			string_buffer << '"';
			if (is_reading_string) {
				is_reading_string = false;
				parsed_list.push_back(string_buffer.str());
				string_buffer.str("");
				string_buffer_contains_data = false;
			}
			else {
				is_reading_string = true;
			}

		}
		else {

			string_buffer << c;
			string_buffer_contains_data = true;

		}
	}


	return parsed_list;
}

bool is_number(std::string string)
{
	if (string.size() < 1)
		return false;

	for (char c : string)
	{
		if (!isdigit(c) && c != '.')
			return false;
	}

	return true;
}

DataType parse_to_data_types(std::vector<std::string> string_list, DataTypes list_type = Proc)
{
	DataType current_list;
	current_list.type = list_type;
	unsigned int current_item_index = 0;
	for (; current_item_index < string_list.size(); ++current_item_index)
	{
		if (string_list.at(current_item_index) == "[" || string_list.at(current_item_index) == "{")
		{
			DataTypes sub_list_type = Proc;
			if (string_list.at(current_item_index) == "{")
				sub_list_type = Tuple;

			std::vector<std::string> new_list;
			int internal_lists = 1;
			while (true) {
				current_item_index++;
				if (string_list.at(current_item_index) == "[" || string_list.at(current_item_index) == "{") {
					internal_lists++;
				}
				else if (string_list.at(current_item_index) == "]" || string_list.at(current_item_index) == "}") {
					internal_lists--;
					if (internal_lists == 0) {
						break;
					}
				}
				new_list.push_back(string_list.at(current_item_index));
			}
			current_list.list.push_back(parse_to_data_types(new_list, sub_list_type));
		}
		else if (is_number(string_list.at(current_item_index)))
		{
			DataType data;
			data.type = Number;
			data.number = atof(string_list.at(current_item_index).c_str());
			current_list.list.push_back(data);
		}
		else if (string_list.at(current_item_index)[0] == '"')
		{
			DataType data;
			data.type = String;
			data.string = string_list.at(current_item_index).substr(1, string_list.at(current_item_index).size() - 2);
			current_list.list.push_back(data);
		}
		else if (string_list.at(current_item_index) == "true" || string_list.at(current_item_index) == "false")
		{
			DataType data;
			data.type = Bool;
			if (string_list.at(current_item_index) == "true")
				data.boolean = true;
			else
				data.boolean = false;
			current_list.list.push_back(data);

		}
		else
		{
			DataType data;
			data.type = Symbol;
			data.string = string_list.at(current_item_index);
			current_list.list.push_back(data);
		}
	}
	return current_list;
}

void print_data(DataType data, int indentation)
{
	if (data.type == Proc)
	{
		std::cout << "p";
		for (auto i : data.list)
			print_data(i, indentation + 1);
		std::cout << std::endl;
	}
	else if (data.type == Tuple)
	{
		std::cout << "t";
		for (auto i : data.list)
			print_data(i, indentation + 1);
		std::cout << std::endl;
	}
	else if (data.type == Symbol)
	{
		for (int i(indentation); i > 0; i--)
			std::cout << "\t";
		std::cout << "Symbol: " << data.string << std::endl;
	}
	else if (data.type == String)
	{
		for (int i(indentation); i > 0; i--)
			std::cout << "\t";
		std::cout << "String: " << data.string << std::endl;
	}
	else if (data.type == Number)
	{
		for (int i(indentation); i > 0; i--)
			std::cout << "\t";
		std::cout << "Number: " << data.number << std::endl;
	}
	else if (data.type == Bool)
	{
		for (int i(indentation); i > 0; i--)
			std::cout << "\t";
		std::cout << "Boolean: " << data.boolean << std::endl;
	}
}


int main()
{
	//auto l = parse_to_data_types(parse_to_string("[println \"Starting \n\"][println \"Starting \n\"][if [== [+ 2 2] [- 8 4]] [println [conc \"Hello, \" \"World!\"]] [println \"Goodbye, Universe\"]]"));

	//auto l = parse_to_data_types(parse_to_string("[= x [+ 2 22]][println x]"));
	
	auto l = parse_to_data_types(parse_to_string("[= print-and-add [fn {a b} [println [+ a b]]]] [print-and-add 2 3]"));

	//print_data(l);

	Enviroment env = get_global_enviroment();
	eval(l, &env);

	//auto l = parse_to_data_types(parse_to_string("[fn {a} s [println a]]"));
	//print_data(l);

	char x;
	std::cin >> x;
}