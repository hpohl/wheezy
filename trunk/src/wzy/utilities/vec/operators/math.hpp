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

}

#endif
