#ifndef WZY_UTILITIES_MATDEF_HPP
#define WZY_UTILTIIES_MATDEF_HPP

#include <cassert>

#include <wzy/utilities/vec.hpp>


namespace wzy {

template <int cols, int rows, class T>
class Matrix {
public:
    Matrix()
    { if (cols == rows) identity(); else zero(); }

    Vector<rows, T>& operator[](size_t i)
    { assert(i < cols); return mData[i]; }

    void identity();
    void zero();

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
        for (int j = 0; j < rows; ++i) {
            if (i == j)
                mData[i][j] = 1.0;
            else
                mData[i][j] = 0.0;
        }
    }
}

template <int cols, int rows, class T>
void Matrix<cols, rows, T>::zero() {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++i) {
            mData[i][j] = 0.0;
        }
    }
}

}

#endif
