#ifndef WZY_UTILITIES_VEC_FUNCTIONS_MATH_HPP
#define WZY_UTILITIES_VEC_FUNCTIONS_MATH_HPP

#include <cmath>

#include <wzy/utilities/helpers/operations.hpp>
#include <wzy/utilities/vec/aliases.hpp>
#include <wzy/utilities/vec/vecfwd.hpp>


namespace wzy {

template <class Tlhs, class Trhs>
const Vector3<Tlhs> cross(const Vector3<Tlhs>& lhs, const Vector3<Trhs>& rhs) {
    return Vector3<Tlhs>(lhs[1] * rhs[2] - lhs[2] * rhs[1],
                         lhs[2] * rhs[0] - lhs[0] * rhs[2],
                         lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}

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
