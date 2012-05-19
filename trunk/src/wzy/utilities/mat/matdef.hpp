#ifndef WZY_UTILITIES_MAT_MATDEF_HPP
#define WZY_UTILITIES_MAT_MATDEF_HPP

#include <utility>

#include <cassert>

#include <wzy/utilities/mat/functions/general.hpp>
#include <wzy/utilities/mat/functions/math.hpp>
#include <wzy/utilities/mat/operators/math.hpp>
#include <wzy/utilities/tmp.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {

template <int rows, int cols, class T>
class Matrix {
public:
    static_assert(rows > 1 && cols > 1, "A matrix has to have at least 2 rows and cols.");

    struct GetIniter {
        struct Identity {
            template <int n, class Tm>
            static void go(Matrix<n, n, Tm>& m)
            { identity(m); }
        };

        struct Zero {
            template <int c, int r, class Tm>
            static void go(Matrix<c, r, Tm>& m)
            { zero(m); }
        };

        typedef typename std::conditional<rows == cols, Identity, Zero>::type type;
    };

    Matrix()
    { GetIniter::type::go(*this); }

    Vector<rows, T>& operator[](size_t i)
    { assert(i < rows); return mData[i]; }

    const Vector<rows, T>& operator[](size_t i) const
    { assert(i < rows); return mData[i]; }

    const T* data() const
    { return reinterpret_cast<const T*>(mData); }

private:
    Vector<cols, T> mData[rows];
};


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
