#ifndef WZY_UTILITIES_VEC_OPERATORS_MATH_HPP
#define WZY_UTILITIES_VEC_OPERATORS_MATH_HPP

#include <utility>

#include <wzy/utilities/vec/vecfwd.hpp>


namespace wzy {

#define WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_OPERATOR(op) \
template <int n, class Tlhs, class Trhs> \
inline const Vector<n, decltype(std::declval<Tlhs>() op std::declval<Trhs>())> \
operator op(const Vector<n, Tlhs>& lhs, const Vector<n, Trhs>& rhs) { \
    Vector<n, decltype(std::declval<Tlhs>() op std::declval<Trhs>())> ret; \
    for (int i = 0; i < n; ++i) \
        ret[i] = lhs[i] op rhs[i]; \
    return ret; \
} \
\
template <int n, class Tlhs, class Trhs> \
inline const Vector<n, decltype(std::declval<Tlhs>() op std::declval<Trhs>())> \
operator op(const Vector<n, Tlhs>& lhs, const Trhs& rhs) { \
    Vector<n, decltype(std::declval<Tlhs>() op std::declval<Trhs>())> ret; \
    for (int i = 0; i < n; ++i) \
        ret[i] = lhs[i] op rhs; \
    return ret; \
} \
\
template <int n, class Tlhs, class Trhs> \
inline const Vector<n, decltype(std::declval<Tlhs>() op std::declval<Trhs>())> \
operator op(const Trhs& rhs, const Vector<n, Tlhs>& lhs) { \
   Vector<n, decltype(std::declval<Tlhs>() op std::declval<Trhs>())> ret; \
    for (int i = 0; i < n; ++i) \
        ret[i] = rhs op lhs[i]; \
    return ret; \
}

WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_OPERATOR(+);
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_OPERATOR(-);
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_OPERATOR(*);
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_OPERATOR(/);
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_OPERATOR(%);


#define WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_ASSIGNOPERATOR(op) \
template <int n, class Tlhs, class Trhs> \
Vector<n, Tlhs>& operator op(Vector<n, Tlhs>& lhs, const Vector<n, Trhs>& rhs) { \
    for (int i = 0; i < n; ++i) \
        lhs[i] op rhs[i]; \
    return lhs; \
} \
\
template <int n, class Tlhs, class Trhs> \
Vector<n, Tlhs>& operator op(Vector<n, Tlhs>& lhs, const Trhs& rhs) { \
    for (int i = 0; i < n; ++i) \
        lhs[i] op rhs; \
    return lhs; \
}

WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_ASSIGNOPERATOR(+=)
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_ASSIGNOPERATOR(-=)
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_ASSIGNOPERATOR(*=)
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_ASSIGNOPERATOR(/=)
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_ASSIGNOPERATOR(%=)
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_ASSIGNOPERATOR(&=)
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_ASSIGNOPERATOR(|=)
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_ASSIGNOPERATOR(^=)
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_ASSIGNOPERATOR(<<=)
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_ASSIGNOPERATOR(>>=)


#define WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_UNARY(op) \
template <int n, class T> \
const Vector<n, T> operator op(const Vector<n, T>& v) { \
    Vector<n, T> ret; \
    for (int i = 0; i < n; ++i) \
        ret[i] = op v[i]; \
    return ret; \
}

WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_UNARY(+)
WZY_UTILITIES_VEC_OPERATORS_MATH_DEFINE_UNARY(-)

}

#endif
