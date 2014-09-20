#include "xigua/record.hpp"

namespace xig {

    data_type record_definition::type() const { return data_type::record_definition; };

    const record_definition &record_definition::as_record_definition() const { return *this; }

    std::vector<record_variable_definition>::const_iterator record_definition::begin() const { return value.cbegin(); }

    std::vector<record_variable_definition>::const_iterator record_definition::end() const { return value.cend(); }

    std::size_t record_definition::size() const { return value.size(); }

    record_definition::operator std::vector<record_variable_definition>() const { return value; }

    std::vector<record_variable_definition> record_definition::as_std_vector() const { return value; }

    bool record_definition::operator<(const data &other) const {
        if (type() == other.type())
            return (value < other.as_record_definition().value);
        return type() < other.type();
    }

    bool record_definition::operator==(const data &other) const {
        if (type() == other.type())
            return value == other.as_record_definition().value;
        return false;
    }

    data_type record_object::type() const { return data_type::record_object; };

    const record_object &record_object::as_record_object() const { return *this; }

    std::vector<record_variable_object>::const_iterator record_object::begin() const { return value.cbegin(); }

    std::vector<record_variable_object>::const_iterator record_object::end() const { return value.cend(); }

    std::size_t record_object::size() const { return value.size(); }

    record_object::operator std::vector<record_variable_object>() const { return value; }

  std::vector<record_variable_object> record_object::as_std_vector() const { return value; }

    bool record_object::operator<(const data &other) const {
        if (type() == other.type())
            return (value < other.as_record_object().value);
        return type() < other.type();
    }

    bool record_object::operator==(const data &other) const {
        if (type() == other.type())
            return value == other.as_record_object().value;
        return false;
    }


  data_ptr make_record_definition(std::vector<record_variable_definition> value) {
    return std::make_shared<record_definition>(value);
  }

  data_ptr make_record_object(data_ptr parent, std::vector<record_variable_object> value) {
    return std::make_shared<record_object>(parent, value);
  }

}
