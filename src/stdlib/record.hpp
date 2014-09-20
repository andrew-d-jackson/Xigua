#pragma once

#include <vector>
#include <set>
#include <functional>
#include <numeric>

#include "xigua/data.hpp"
#include "xigua/enviroment.hpp"
#include "xigua/error.hpp"
#include "xigua/evaluate.hpp"
#include "stdlib/utils.hpp"

namespace xig {
namespace stdlib {

    class define_record : public method {
        int amount_of_arguments() const { return 2; }
        bool should_evaluate_arguments() const { return false; }

        data_ptr run(call_info fci) {
            if (fci.args.at(0)->type() != data_type::symbol)
                throw error(error_type::invalid_arguments, "Not A Symbol", fci.debug);

            if (fci.args.at(1)->type() != data_type::tuple)
                throw error(error_type::invalid_arguments, "Not A Tuple", fci.debug);

            auto ret = std::map<std::string, data_ptr>();
            for (const auto &i : fci.args.at(1)->as_tuple()) {
                if (i->type() != data_type::symbol)
                    throw error(error_type::invalid_arguments, "Not A Symbol", fci.debug);

                ret[i->as_symbol().as_std_string()] = make_none();
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

            auto ret = std::map<std::string, data_ptr>();
            for (const auto &i : fci.args.at(1)->as_tuple()) {
                if (i->type() != data_type::symbol)
                    throw error(error_type::invalid_arguments, "Not A Symbol", fci.debug);

                ret[i->as_symbol().as_std_string()] = make_none();
            }
            return make_record_definition(ret);
        }
    };


}
}
