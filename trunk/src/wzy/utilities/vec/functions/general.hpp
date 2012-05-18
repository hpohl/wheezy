#ifndef WZY_UTILITIES_VEC_FUNCTIONS_HPP
#define WZY_UTILITIES_VEC_FUNCTIONS_HPP

#include <iostream>
#include <type_traits>

#include <wzy/utilities/helpers/operations.hpp>
#include <wzy/utilities/vec/vecfwd.hpp>
#include <wzy/utilities/vec/info.hpp>


namespace wzy {

namespace detail {
namespace vec {

// Forwards
template <int begin, int nv, class Tv, int nav, class Tav, class... Args>
void assign(Vector<nv, Tv>& v, Vector<nav, Tav>&& av, Args&&... args);

template <int begin, int n, class T>
void assign(Vector<n, T>& v) {
    static_assert(begin == n, "Not enough assignment parameters.");
}

template <int begin, int n, class T, class First, class... Args>
typename std::enable_if<!IsVec<typename std::remove_reference<First>::type>::value>::type
assign(Vector<n, T>& v, First&& first, Args&&... args) {
    static_assert(begin < n, "Too many assignment parameters.");
    v[begin] = first;
    detail::vec::assign<begin + 1>(v, std::forward<Args>(args)...);
}

template <int begin, int nv, class Tv, int nav, class Tav, class... Args>
void assign(Vector<nv, Tv>& v, Vector<nav, Tav>&& av, Args&&... args) {
    static_assert((begin + nav) <= nv, "Too many assignment parameters.");
    operate<op::Assign, nav>(v.data() + begin, av);
    detail::vec::assign<begin + nav>(v, std::forward<Args>(args)...);
}

}
}

template <int n, class T, class... Args>
void assign(Vector<n, T>& v, Args&&... args)
{ detail::vec::assign<0>(v, std::forward<Args>(args)...); }


// ---------------------------------------
template <int n, class T>
void print(const Vector<n, T>& v) {
    for (int i = 0; i < n; ++i) {
        std::cout << v[i];
        if ((i + 1) < n)
            std::cout << ", ";
    }
    std::cout << std::endl;
}

}

#endif
