#pragma once

#include <map>
#include <string>
#include <memory>

#include "xigua/data.hpp"

namespace xig {

    struct record_variable {
        std::string name;
        std::vector<process> guards;
    };

    class record_definition : public data {
    private:
        std::map<std::string, data_ptr> value;

    public:
        record_definition(std::map<std::string, data_ptr> value) : value(value) {}
        virtual ~record_definition() {}

        virtual data_type type() const;
        virtual const record_definition &as_record_definition() const;

        std::map<std::string, data_ptr>::const_iterator begin() const;
        std::map<std::string, data_ptr>::const_iterator end() const;
        std::size_t size() const;

        operator std::map<std::string, data_ptr>() const;
        std::map<std::string, data_ptr> as_std_map() const;

        virtual bool operator<(const data &other) const;
        virtual bool operator==(const data &other) const;
    };

    class record_object : public data {
    private:
        data_ptr definition;
        std::vector<std::tuple<record_variable*, data_ptr>>;
        std::map<std::string, data_ptr> value;

    public:
        record_object(data_ptr definition, std::map<std::string, data_ptr> value) : definition(definition), value(value) {}
        virtual ~record_object() {}

        virtual data_type type() const;
        virtual const record_object &as_record_object() const;

        std::map<std::string, data_ptr>::const_iterator begin() const;
        std::map<std::string, data_ptr>::const_iterator end() const;
        std::size_t size() const;

        operator std::map<std::string, data_ptr>() const;
        std::map<std::string, data_ptr> as_std_map() const;

        virtual bool operator<(const data &other) const;
        virtual bool operator==(const data &other) const;
    };


    extern data_ptr make_record_definition(std::map<std::string, data_ptr> val);
    extern data_ptr make_record_object(data_ptr parent, std::map<std::string, data_ptr> val);
}
