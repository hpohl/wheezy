#ifndef WZY_UTILITIES_MAT_ALIASES_HPP
#define WZY_UTILITIES_MAT_ALIASES_HPP

#include <wzy/utilities/mat/matfwd.hpp>


namespace wzy {

template <class T>
using Matrix2 = Matrix<2, 2, T>;

template <class T>
using Matrix3 = Matrix<3, 3, T>;

template <class T>
using Matrix4 = Matrix<4, 4, T>;


typedef Matrix2<float> Matrix2f;
typedef Matrix3<float> Matrix3f;
typedef Matrix4<float> Matrix4f;

}

#endif
