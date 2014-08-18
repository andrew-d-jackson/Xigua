#include "xigua/symbol.hpp"

namespace xig {

data_type symbol::type() const { return data_type::symbol; };

const symbol &symbol::as_symbol() const { return *this; }

data_ptr make_symbol(std::string str) { return std::make_shared<symbol>(str); }
}
