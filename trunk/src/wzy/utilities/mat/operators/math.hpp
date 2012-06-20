#ifndef WZY_UTILITIES_MAT_OPERATORS_MATH_HPP
#define WZY_UTILITIES_MAT_OPERATORS_MATH_HPP

#include <wzy/utilities/helpers/operations.hpp>
#include <wzy/utilities/mat/matfwd.hpp>
#include <wzy/utilities/tmp.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {

template <int rowslhs, int colslhs, class Tlhs,
          int rowsrhs, int colsrhs, class Trhs>
const Matrix<tmp::Highest<rowslhs, rowsrhs>::value, tmp::Highest<colslhs, colsrhs>::value,
decltype(std::declval<Tlhs>() * std::declval<Trhs>())>
operator*(const Matrix<rowslhs, colslhs, Tlhs>& lhs, const Matrix<rowsrhs, colsrhs, Trhs>& rhs) {

    static_assert(rowslhs == colsrhs, "Number of rows of the left and coloumns of the right have to be equal.");
    static_assert(colslhs == rowsrhs, "Number of coloums of the left and rows of the right have to be equal.");

    constexpr int maxcols = tmp::Highest<colslhs, colsrhs>::value;
    constexpr int maxrows = tmp::Highest<rowslhs, rowsrhs>::value;

    typedef decltype(std::declval<Tlhs>() * std::declval<Trhs>()) RetT;

    Matrix<maxcols, maxrows, RetT> m;

    for (int row = 0; row < maxrows; ++row)
        for (int col = 0; col < maxcols; ++col)
            m[row][col] = dot(lhs[row], coloumn(rhs, col));


    return m;
}


template <int rowslhs, int colslhs, class Tlhs,
          int rowsrhs, int colsrhs, class Trhs>
Matrix<rowslhs, colslhs, Tlhs>& operator*=(Matrix<rowslhs, colslhs, Tlhs>& lhs, const Matrix<rowsrhs, colsrhs, Trhs>& rhs)
{ lhs = lhs * rhs; return lhs; }


#define WZY_UTILITIES_MAT_OPERATORS_DEFINE_UNARY(op) \
template <int rows, int cols, class T> \
const Matrix<rows, cols, T> operator op(const Matrix<rows, cols, T>& m) { \
    Matrix<rows, cols, T> ret; \
    for (int row = 0; row < rows; ++row) \
        for (int col = 0; col < cols; ++col) \
            ret[row][col] = op m[row][col]; \
    return ret; \
}

WZY_UTILITIES_MAT_OPERATORS_DEFINE_UNARY(+)
WZY_UTILITIES_MAT_OPERATORS_DEFINE_UNARY(-)


}

#endif
