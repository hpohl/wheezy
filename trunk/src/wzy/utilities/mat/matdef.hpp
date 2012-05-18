#ifndef WZY_UTILITIES_MAT_MATDEF_HPP
#define WZY_UTILTIIES_MAT_MATDEF_HPP

#include <utility>

#include <cassert>

#include <wzy/utilities/tmp.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {

template <int cols, int rows, class T>
class Matrix {
public:
    static_assert(cols > 1 && rows > 1, "A matrix has to have at least 2 cols and rows.");

    Matrix()
    { if (cols == rows) identity(); else zero(); }

    Vector<rows, T>& operator[](size_t i)
    { assert(i < cols); return mData[i]; }

    const Vector<rows, T>& operator[](size_t i) const
    { assert(i < cols); return mData[i]; }

    void identity();
    void zero();

    template <class... Args>
    void translate(Args&&... args);

    const T* data() const
    { return reinterpret_cast<const T*>(mData); }

private:
    Vector<rows, T> mData[cols];
};


// -----------------------------------------
template <int cols, int rows, class T>
void Matrix<cols, rows, T>::identity() {
    static_assert(cols == rows, "Number of coloums have to equal the rows.");
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            if (i == j)
                mData[i][j] = 1.0;
            else
                mData[i][j] = 0.0;
        }
    }
}

template <int cols, int rows, class T>
void Matrix<cols, rows, T>::zero() {
    for (int i = 0; i < cols; ++i)
        for (int j = 0; j < rows; ++i)
            mData[i][j] = 0.0;
}

namespace detail {

template <int coln, int cols, int rows, class Tmat, int n, class Tvec>
void translate(Matrix<cols, rows, Tmat>& m, const Vector<n, Tvec>& vec) {
    static_assert(cols == (n + 1), "Unable to translate vector: Invalid dimensions.");
    for (int i = 0; i < (cols - 1); ++i) {
        m[i][rows - 1] = vec[i];
    }
}

template <int coln, int cols, int rows, class T, class First, class... Args>
void translate(Matrix<cols, rows, T>& m, First&& first, Args&&... args) {
    m[coln][rows - 1] = first;
    translate<coln + 1>(m, std::forward<Args>(args)...);
}

}

template <int cols, int rows, class T>
template <class... Args>
void Matrix<cols, rows, T>::translate(Args&&... args) {
    detail::translate<0>(*this, std::forward<Args>(args)...);
}


// ---------------------------------------------
template <int colslhs, int rowslhs, class Tlhs,
          int colsrhs, int rowsrhs, class Trhs>
const Matrix<tmp::Biggest<colslhs, colsrhs>::value, tmp::Biggest<rowslhs, rowsrhs>::value, typename std::common_type<Tlhs, Trhs>::type>
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


// -----------------------------
template <class T>
using Matrix2 = Matrix<2, 2, T>;

template <class T>
using Matrix3 = Matrix<3, 3, T>;

template <class T>
using Matrix4 = Matrix<4, 4, T>;


typedef Matrix4<float> Matrix4f;

}

#endif
