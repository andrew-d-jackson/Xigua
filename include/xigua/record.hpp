#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>

#include "xigua/data.hpp"

namespace xig {

    struct record_variable_definition {
      const std::string name;
      const std::vector<data_ptr> guards;
      bool operator==(record_variable_definition other) const{
        return name == other.name && guards == other.guards;
      }
      bool operator<(record_variable_definition other) const{
        return name < other.name && guards < other.guards;
      }
    };

    struct record_variable_object {
      const record_variable_definition* definition;
      const data_ptr value;
      bool operator==(record_variable_object other) const{
        return definition == other.definition && value == other.value;
      }
      bool operator<(record_variable_object other) const{
        return definition < other.definition && value < other.value;
      }
    };

    class record_definition : public data {
    private:
        std::vector<record_variable_definition> value;

    public:
        record_definition(std::vector<record_variable_definition> value) : value(value) {}
        virtual ~record_definition() {}

        virtual data_type type() const;
        virtual const record_definition &as_record_definition() const;

        std::vector<record_variable_definition>::const_iterator begin() const;
        std::vector<record_variable_definition>::const_iterator end() const;
        std::size_t size() const;

        operator std::vector<record_variable_definition>() const;
        std::vector<record_variable_definition> as_std_vector() const;

        virtual bool operator<(const data &other) const;
        virtual bool operator==(const data &other) const;
    };

    class record_object : public data {
    private:
        data_ptr definition;
        std::vector<record_variable_object> value;

    public:
        record_object(data_ptr definition, std::vector<record_variable_object> value) : definition(definition), value(value) {}
        virtual ~record_object() {}

        virtual data_type type() const;
        virtual const record_object &as_record_object() const;

        std::vector<record_variable_object>::const_iterator begin() const;
        std::vector<record_variable_object>::const_iterator end() const;
        std::size_t size() const;

        operator std::vector<record_variable_object>() const;
        std::vector<record_variable_object> as_std_vector() const;

        virtual bool operator<(const data &other) const;
        virtual bool operator==(const data &other) const;
    };


    extern data_ptr make_record_definition(std::vector<record_variable_definition> value);

    extern data_ptr make_record_object(data_ptr parent, std::vector<record_variable_object> value);
}
