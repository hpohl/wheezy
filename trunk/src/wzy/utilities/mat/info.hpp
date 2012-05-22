#ifndef WZY_UTILITIES_MAT_INFO_HPP
#define WZY_UTILITIES_MAT_INFO_HPP

#include <type_traits>


namespace wzy {

namespace detail {
namespace mat {
struct MatID;
}
}

template <class T>
struct IsMatrix : public std::is_base_of<detail::mat::MatID, T> { };

}

#endif
