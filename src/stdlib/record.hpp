#pragma once

#include <vector>
#include <set>
#include <functional>
#include <numeric>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"
#include "xigua/evaluate.hpp"
#include "xigua/record.hpp"
#include "stdlib/utils.hpp"

namespace xig {
namespace stdlib {

    class define_record : public method {
        int amount_of_arguments() const { return 1; }
        bool should_evaluate_arguments() const { return false; }

        data_ptr run(call_info fci) {
            if (fci.args.at(0)->type() != data_type::tuple)
                throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

            auto ret = std::vector<record_variable_definition>();
            for (const auto &i : fci.args.at(0)->as_tuple()) {
                if (i->type() != data_type::keyword)
                    throw error(error_type::invalid_arguments, "Not A Keyword", fci.debug);

                ret.push_back(record_variable_definition{i->as_keyword().as_std_string(), {}});
            }
            return make_record_definition(ret);
        }
    };

    class make : public method {
        int amount_of_arguments() const { return 2; }

        data_ptr run(call_info fci) {
            if (fci.args.at(0)->type() != data_type::record_definition)
                throw error(error_type::invalid_arguments, "Not A Record Definition", fci.debug);

            if (fci.args.at(1)->type() != data_type::tuple)
                throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

            auto ret = std::vector<record_variable_object>();

            auto j = fci.args.at(1)->as_tuple().begin();
            for (const auto &i: fci.args.at(0)->as_record_definition()) {
              ret.push_back(record_variable_object{ &i, *(j++) });
            }

            return make_record_object(fci.args.at(0), ret);
        }
    };


}
}
