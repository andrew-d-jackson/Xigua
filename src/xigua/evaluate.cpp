#include "xigua/evaluate.hpp"

namespace xig {

bool isPrimitive(data &d) {
  switch (d.type()) {
  case data_type::integer:
  case data_type::decimal:
  case data_type::none:
  case data_type::boolean:
  case data_type::string:
  case data_type::keyword:
    return true;
  default:
    return false;
  }
}

data lookupSymbol(enviroment &env, data input_data, debug_info debug) {
  auto sym = input_data.as_symbol();
  data *symbol_value = env.find(input_data.as_symbol());
  if (symbol_value == nullptr) {
    throw xig::error(xig::error_type::invalid_arguments,
                     "Cannot Find Symbol: " + input_data.as_symbol(), debug);
  }
  return *symbol_value;
}

data processSymbolProcess(enviroment &env, data input_data, int loc,
                          debug_info debug) {
  switch (input_data.as_process().at(loc).type()) {
  case data_type::symbol:
    debug.function_call_list.push_back(
        input_data.as_process().at(loc).as_symbol());
  case data_type::process: {
    std::vector<data> new_proc_data = input_data.as_process();
    new_proc_data.at(loc) =
        evaluate(env, input_data.as_process().at(loc), debug);
    input_data = data(data_type::process, new_proc_data);
    break;
  }
  default:
    break;
  }
  return input_data;
}

data handleProcess(enviroment &env, data input_data, debug_info debug) {
  if (input_data.as_process().size() == 0)
    return make_none();

  // if first arg is symbol or process, evaluate it
  input_data = processSymbolProcess(env, input_data, 0, debug);

  if (input_data.as_process().at(0).type() == data_type::function) {
    auto process_copy = input_data.as_process();
    auto firstElement = process_copy.begin() + 1;
    auto lastElement = process_copy.end();
    std::vector<data> functionArgs(firstElement, lastElement);

    return input_data.as_process().at(0).as_function().call(
        {functionArgs, env, debug});
  }

  if (input_data.as_process().size() == 3) {
    input_data = processSymbolProcess(env, input_data, 1, debug);
    if (input_data.as_process().at(1).type() == data_type::function) {
      std::vector<data> functionArgs = {input_data.as_process().at(0),
                                        input_data.as_process().at(2)};
      return input_data.as_process().at(1).as_function().call(
          {functionArgs, env, debug});
    }
  }

  data return_value = make_none();
  for (data item : input_data.as_process())
    return_value = evaluate(env, item, debug);
  return return_value;
}

data handleTuple(enviroment &env, data input_data, debug_info debug) {
  std::vector<data> new_tuple_data;
  for (auto data : input_data.as_tuple()) {
    new_tuple_data.push_back(evaluate(env, data, debug));
  }
  return data(data_type::tuple, new_tuple_data);
}

data handleMap(enviroment &env, data input_data, debug_info debug) {
  std::map<data, data> new_map_data;
  for (auto data : input_data.as_map()) {
    auto first = data.first;
    auto second = data.second;
    new_map_data[evaluate(env, first, debug)] = evaluate(env, second, debug);
  }
  return make_map(new_map_data);
}

data evaluate(enviroment &env, data input_data, debug_info debug) {
  if (isPrimitive(input_data))
    return input_data;

  if (input_data.type() == data_type::symbol)
    return lookupSymbol(env, input_data, debug);

  if (input_data.type() == data_type::process)
    return handleProcess(env, input_data, debug);

  if (input_data.type() == data_type::tuple)
    return handleTuple(env, input_data, debug);

  if (input_data.type() == data_type::map)
    return handleMap(env, input_data, debug);

  return make_none();
}
}
