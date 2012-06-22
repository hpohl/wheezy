#ifndef WZY_UTILITIES_VEC_FUNCTIONS_MATH_HPP
#define WZY_UTILITIES_VEC_FUNCTIONS_MATH_HPP

#include <cmath>

#include <wzy/utilities/helpers/operations.hpp>
#include <wzy/utilities/vec/vecfwd.hpp>


namespace wzy {

template <int n, class Tlhs, class Trhs>
decltype(std::declval<Tlhs>() * std::declval<Trhs>())
dot(const Vector<n, Tlhs>& lhs, const Vector<n, Trhs>& rhs) {
    decltype(std::declval<Tlhs>() * std::declval<Trhs>()) ret = 0;
    for (int i = 0; i < n; ++i)
        ret += lhs[i] * rhs[i];
    return ret;
}

template <int n, class T>
float length(const Vector<n, T>& v) {
    float len = 0;
    for (int i = 0; i < n; ++i)
        len += v[i] * v[i];
    return std::sqrt(len);
}

template <int n, class T>
void normalise(Vector<n, T>& v) {
    for (int i = 0; i < n; ++i)
        v[i] /= length(v);
}

}

#endif
