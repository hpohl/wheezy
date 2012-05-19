#ifndef WZY_UTILITIES_MAT_FUNCTIONS_MATH_HPP
#define WZY_uTILITIES_MAT_FUNCTIONS_MATH_HPP

#include <wzy/utilities/mat/operators/math.hpp>
#include <wzy/utilities/mat/matfwd.hpp>
#include <wzy/utilities/vec/vecfwd.hpp>
#include <wzy/utilities/vec/info.hpp>


namespace wzy {

namespace detail {
namespace mat {

template <int begin, int rows, int cols, class T>
void translate(Matrix<cols, rows, T>& m) {
    static_assert((begin + 1) == rows, "Not enough translate parameters.");
}

template <int begin, int rows, int cols, class T, class First, class... Args>
typename std::enable_if<!IsVec<First>::value>::type
translate(Matrix<cols, rows, T>& m, const First& first, const Args&... args) {
    static_assert((begin + 1) < rows, "Too many translate parameters.");
    m[cols - 1][begin] += first;
    translate<begin + 1>(m, args...);
}

template <int begin, int rows, int cols, class T, int n, class Tv, class... Args>
void translate(Matrix<cols, rows, T>& m, const Vector<n, Tv>& v, const Args&... args) {
    static_assert((begin + 1) < rows, "Too many translate parameters.");
    for (int i = 0; i < n; ++i)
        m[cols - 1][begin + i] += v[i];
    translate<begin + n>(m, args...);
}

}
}

template <int rows, int cols, class T, class... Args>
void translate(Matrix<cols, rows, T>& m, Args&&... args)
{ detail::mat::translate<0>(m, std::forward<Args>(args)...); }

}

#endif
