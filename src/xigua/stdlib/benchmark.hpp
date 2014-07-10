#pragma once

#include <vector>
#include <chrono>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/evaluate.hpp"
#include "xigua/error.hpp"

#include "xigua/stdlib/utils.hpp"

namespace xig {
namespace stdlib {

class benchmark : public method {
  int amount_of_arguments() const { return 3; }
  bool should_evaluate_arguments() const { return false; }

  data run(std::vector<data> args, enviroment &env,
           std::vector<std::string> fcl) {
    if (args.at(0).type() != data_type::string)
      throw error(error_type::invalid_arguments, "Not A String", fcl);

    if (args.at(1).type() != data_type::integer)
      throw error(error_type::invalid_arguments, "Not A integer", fcl);

    if (args.at(2).type() != data_type::process)
      throw error(error_type::invalid_arguments, "Not A Process", fcl);

    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();

    auto times = args.at(1).as_integer();
    for (long i = 0; i < times; i++) {
      evaluate(env, args.at(2), fcl);
    }

    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    auto dur =
        std::chrono::duration_cast<std::chrono::duration<int, std::milli> >(
            end_time - start_time).count();
    auto average = dur / times;

    std::cout << "Benchmark: " << args.at(0).as_string() << std::endl
              << "Total Time: " << dur << "ms" << std::endl
              << "Average Time: " << average << "ms" << std::endl;

    return make_none();
  }
};
}
}
