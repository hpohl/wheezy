#ifndef WZY_UTILITIES_MAT_FUNCTIONS_MATH_HPP
#define WZY_uTILITIES_MAT_FUNCTIONS_MATH_HPP

#include <wzy/utilities/mat/operators/math.hpp>
#include <wzy/utilities/mat/matfwd.hpp>
#include <wzy/utilities/vec/vecfwd.hpp>
#include <wzy/utilities/vec/info.hpp>


namespace wzy {

template <int rows, int cols, class T, int n, class Tv>
void translate(Matrix<cols, rows, T>& m, const Vector<n, Tv>& v) {
    static_assert(rows - 1 == n, "Invalid translation vector.");

    Matrix<cols, rows, T> transm;
    for (int i = 0; i + 1 < rows; ++i)
        transm[i][cols - 1] = v[i];

    m *= transm;
}

}

#endif
