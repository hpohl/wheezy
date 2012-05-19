#ifndef WZY_UTILITIES_MAT_OPERATORS_MATH_HPP
#define WZY_UTILITIES_MAT_OPERATORS_MATH_HPP

#include <wzy/utilities/helpers/operations.hpp>
#include <wzy/utilities/mat/matfwd.hpp>
#include <wzy/utilities/tmp.hpp>


namespace wzy {

template <int colslhs, int rowslhs, class Tlhs,
          int colsrhs, int rowsrhs, class Trhs>
const Matrix<tmp::Biggest<colslhs, colsrhs>::value, tmp::Biggest<rowslhs, rowsrhs>::value, decltype(std::declval<Tlhs>() * std::declval<Trhs>())>
operator*(const Matrix<colslhs, rowslhs, Tlhs>& lhs, const Matrix<colsrhs, rowsrhs, Trhs>& rhs) {

    static_assert(colslhs == rowsrhs, "Number of coloums of the left and rows of the right have to be equal.");
    static_assert(rowslhs == colsrhs, "Number of rows of the left and coloumns of the right have to be equal.");

    constexpr int maxcols = tmp::Biggest<colslhs, colsrhs>::value;
    constexpr int maxrows = tmp::Biggest<rowslhs, rowsrhs>::value;

    Matrix<maxcols, maxrows, typename std::common_type<Tlhs, Trhs>::type> m;

    for (int col = 0; col < maxcols; ++col) {
        for (int row = 0; row < maxrows; ++row) {

        }
    }
}

}

#endif
