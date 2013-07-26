#pragma once

#include <vector>
#include <functional>
#include <limits>

#include "../datatype.hpp"
#include "../enviroment.hpp"


namespace Xigua
{
	namespace Functions
	{
		namespace Math
		{

			DataType less_than(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Number || inputs.at(1).type() != DataTypes::Number) {
					std::cout << "Not a Number";
					exit(1);
				}
				bool repeating_args = false;
				if (inputs.size() > 2) {
					repeating_args = true;
					for (auto item : inputs.at(2).tuple()){
						if (item.type() != DataTypes::Number){
							std::cout << "Not a Number";
							exit(1);
						}
					}

				}

				if (!(inputs.at(0).number() < inputs.at(1).number()))
					return DataType(DataTypes::Bool, false);

				if (repeating_args){
					long double last_number = inputs.at(1).number();

					for (const auto & input : inputs.at(2).tuple()) {	
						if (last_number < input.number())
							last_number = input.number();
						else
							return DataType(DataTypes::Bool, false);
					}

				}

				return DataType(DataTypes::Bool, true);
			}

			DataType greater_than(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Number || inputs.at(1).type() != DataTypes::Number) {
					std::cout << "Not a Number";
					exit(1);
				}
				bool repeating_args = false;
				if (inputs.size() > 2) {
					repeating_args = true;
					for (auto item : inputs.at(2).tuple()){
						if (item.type() != DataTypes::Number){
							std::cout << "Not a Number";
							exit(1);
						}
					}

				}

				if (!(inputs.at(0).number() > inputs.at(1).number()))
					return DataType(DataTypes::Bool, false);

				if (repeating_args){
					long double last_number = inputs.at(1).number();

					for (const auto & input : inputs.at(2).tuple()) {	
						if (last_number > input.number())
							last_number = input.number();
						else
							return DataType(DataTypes::Bool, false);
					}

				}

				return DataType(DataTypes::Bool, true);
			}

			DataType equal_to(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Number || inputs.at(1).type() != DataTypes::Number) {
					std::cout << "Not a Number";
					exit(1);
				}
				bool repeating_args = false;
				if (inputs.size() > 2) {
					repeating_args = true;
					for (auto item : inputs.at(2).tuple()){
						if (item.type() != DataTypes::Number){
							std::cout << "Not a Number";
							exit(1);
						}
					}

				}

				if (!(inputs.at(0).number() == inputs.at(1).number()))
					return DataType(DataTypes::Bool, false);

				if (repeating_args){
					long double last_number = inputs.at(1).number();

					for (const auto & input : inputs.at(2).tuple()) {	
						if (last_number == input.number())
							last_number = input.number();
						else
							return DataType(DataTypes::Bool, false);
					}

				}

				return DataType(DataTypes::Bool, true);
			}

			DataType add(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Number || inputs.at(1).type() != DataTypes::Number) {
					std::cout << "Not a Number";
					exit(1);
				}
				bool repeating_args = false;
				if (inputs.size() > 2) {
					repeating_args = true;
					for (auto item : inputs.at(2).tuple()){
						if (item.type() != DataTypes::Number){
							std::cout << "Not a Number";
							exit(1);
						}
					}

				}

				long double result = inputs.at(0).number();
				result += inputs.at(1).number();

				if (repeating_args){
					for (const auto & input : inputs.at(2).tuple()) {	
						result += input.number();
					}
				}

				return DataType(DataTypes::Number, result);
			}

			DataType minus(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Number || inputs.at(1).type() != DataTypes::Number) {
					std::cout << "Not a Number";
					exit(1);
				}
				bool repeating_args = false;
				if (inputs.size() > 2) {
					repeating_args = true;
					for (auto item : inputs.at(2).tuple()){
						if (item.type() != DataTypes::Number){
							std::cout << "Not a Number";
							exit(1);
						}
					}

				}

				long double result = inputs.at(0).number();
				result -= inputs.at(1).number();

				if (repeating_args){
					for (const auto & input : inputs.at(2).tuple()) {	
						result -= input.number();
					}
				}

				return DataType(DataTypes::Number, result);
			}

			DataType multiply(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Number || inputs.at(1).type() != DataTypes::Number) {
					std::cout << "Not a Number";
					exit(1);
				}
				bool repeating_args = false;
				if (inputs.size() > 2) {
					repeating_args = true;
					for (auto item : inputs.at(2).tuple()){
						if (item.type() != DataTypes::Number){
							std::cout << "Not a Number";
							exit(1);
						}
					}

				}

				long double result = inputs.at(0).number();
				result *= inputs.at(1).number();

				if (repeating_args){
					for (const auto & input : inputs.at(2).tuple()) {	
						result *= input.number();
					}
				}

				return DataType(DataTypes::Number, result);
			}

			DataType divide(std::vector<DataType> inputs, Enviroment* enviroment)
			{
				if (inputs.at(0).type() != DataTypes::Number || inputs.at(1).type() != DataTypes::Number) {
					std::cout << "Not a Number";
					exit(1);
				}
				bool repeating_args = false;
				if (inputs.size() > 2) {
					repeating_args = true;
					for (auto item : inputs.at(2).tuple()){
						if (item.type() != DataTypes::Number){
							std::cout << "Not a Number";
							exit(1);
						}
					}

				}

				long double result = inputs.at(0).number();
				result /= inputs.at(1).number();

				if (repeating_args){
					for (const auto & input : inputs.at(2).tuple()) {	
						result /= input.number();
					}
				}

				return DataType(DataTypes::Number, result);
			}

		}
	}
}