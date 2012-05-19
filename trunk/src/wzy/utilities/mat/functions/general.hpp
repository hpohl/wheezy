#ifndef WZY_UTILITIES_MAT_FUNCTIONS_GENERAL_HPP
#define WZY_UTILITIES_MAT_FUNCTIONS_GENERAL_HPP

#include <iostream>

#include <wzy/utilities/vec/functions/general.hpp>
#include <wzy/utilities/mat/matfwd.hpp>


namespace wzy {

namespace detail {
namespace mat {

template <int begin, int rows, int cols, class T>
void assign(Matrix<rows, cols, T>& m) {
    static_assert((begin + 1) == rows * cols, "Not enough assignment parameters.");
}

}
}

template <int rows, int cols, class T, class... Args>
void assign(Matrix<rows, cols, T>& m, Args&&... args)
{ detail::mat::assign<0>(m, std::forward<Args>(args)...); }

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
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            std::cout << m[col][row];
            if (col < (cols - 1))
                std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

template <int rows, int cols, class T>
void zero(Matrix<rows, cols, T>& m) {
    for (int i = 0; i < cols; ++i)
        for (int j = 0; j < rows; ++j)
            m[i][j] = 0;
}

}

#endif
