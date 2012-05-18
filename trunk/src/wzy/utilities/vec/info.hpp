#ifndef WZY_UTILITIES_VEC_INFO_HPP
#define WZY_UTILITIES_VEC_INFO_HPP

#include <type_traits>


namespace wzy {

namespace detail {
namespace vec {
struct BaseVec;
}
}

template <class T>
struct IsVec : public std::is_base_of<detail::vec::BaseVec, T> { };

}

#endif
