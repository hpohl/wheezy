#ifndef WZY_UTILITIES_MAT_FUNCTIONS_GENERAL_HPP
#define WZY_UTILITIES_MAT_FUNCTIONS_GENERAL_HPP

#include <iostream>

#include <cmath>

#include <wzy/utilities/vec/functions/general.hpp>
#include <wzy/utilities/mat/info.hpp>
#include <wzy/utilities/mat/matfwd.hpp>
#include <wzy/utilities/tmp.hpp>


namespace wzy {

namespace detail {
namespace mat {

template <int begin, int rows, int cols, class T>
void assign(Matrix<rows, cols, T>& m) {
    static_assert(begin == rows * cols, "Not enough assignment parameters.");
}

template <int begin, int rows, int cols, class T, class First>
typename std::enable_if<begin == 0 && !IsMatrix<First>::value>::type
assign(Matrix<rows, cols, T>& m, const First& first) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            m[i][j] = first;
}

template <int begin, int rows, int cols, class T, int rowsv, int colsv, class Tv>
typename std::enable_if<begin == 0>::type
assign(Matrix<rows, cols, T>& m, const Matrix<rowsv, colsv, Tv>& v) {
    constexpr int mrows = tmp::Lowest<rows, rowsv>::value;
    constexpr int mcols = tmp::Lowest<cols, colsv>::value;

    for (int row = 0; row < mrows; ++row)
        for (int col = 0; col < mcols; ++col)
            m[row][col] = v[row][col];

    for (int row = rowsv; row < rows; ++row)
        for (int col = colsv; col < cols; ++col)
            if (row == col)
                m[row][col] = 1;
            else
                m[row][col] = 0;
}

template <int begin, int rows, int cols, class T, class First, class... Args>
typename std::enable_if<!IsVec<First>::value && !IsMatrix<First>::value>::type
assign(Matrix<rows, cols, T>& m, const First& first, const Args&... args) {
    static_assert(begin < cols * rows, "Too many assignment parameters.");
    m[std::floor(begin / cols)][begin % cols] = first;
    assign<begin + 1>(m, args...);
}

template <int begin, int rows, int cols, class Tm, int n, class Tv, class... Args>
void assign(Matrix<rows, cols, Tm>& m, const Vector<n, Tv>& v, const Args&... args) {
    static_assert(begin + n - 1 < cols * rows, "Too many assignment parameters.");
    for (int i = 0; i < n; ++i)
        m[std::floor((begin + i) / cols)][(begin + i) % cols] = v[i];
    assign<begin + n>(m, args...);
}

}
}

template <int rows, int cols, class T, class... Args>
void assign(Matrix<rows, cols, T>& m, Args&&... args)
{ detail::mat::assign<0>(m, std::forward<Args>(args)...); }

template <int rows, int cols, class T>
const Vector<rows, T> coloumn(const Matrix<rows, cols, T>& m, int idx) {
    assert(idx < cols);
    Vector<rows, T> ret;
    for (int i = 0; i < rows; ++i)
        ret[i] = m[i][idx];
    return ret;
}

template <int rows, int cols, class T>
void identity(Matrix<rows, cols, T>& m) {
    static_assert(rows == cols, "Cols have to equal rows.");
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (i == j)
                m[i][j] = 1;
            else
                m[i][j] = 0;
}

template <int rows, int cols, class T>
void print(const Matrix<rows, cols, T>& m) {
    for (int row = 0; row < rows; ++row)
        print(m[row]);
}

template <int rows, int cols, class T>
void zero(Matrix<rows, cols, T>& m) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            m[i][j] = 0;
}

}

#endif
