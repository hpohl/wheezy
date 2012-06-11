#ifndef WZY_UTILITIES_MAT_FUNCTIONS_MATH_HPP
#define WZY_uTILITIES_MAT_FUNCTIONS_MATH_HPP

#include <cmath>

#include <wzy/utilities/mat/operators/math.hpp>
#include <wzy/utilities/mat/matfwd.hpp>
#include <wzy/utilities/vec/vecfwd.hpp>
#include <wzy/utilities/vec/info.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {

template <class T>
void orthographic(Matrix<4, 4, T>& m,
                  float left, float right,
                  float bottom, float top,
                  float nearVal,
                  float farVal) {
    identity(m);
    m[0][0] = 2.0 / (right - left);
    m[0][3] = -(right + left) / (right - left);
    m[1][1] = 2.0 / (top - bottom);
    m[1][3] = -(top + bottom) / (top - bottom);
    m[2][2] = -2.0 / (farVal - nearVal);
    m[2][3] = -(farVal + nearVal) / (farVal - nearVal);
}

template <class T>
void perspective(Matrix<4, 4, T>& m, float fovy, float aspect, float zNear, float zFar) {
    identity(m);
    m[0][0] = std::atan(degreesToRadians(fovy / 2.0)) / aspect;
    m[1][1] = std::atan(degreesToRadians(fovy / 2.0));
    m[2][2] = -((zFar + zNear) / (zFar - zNear));
    m[2][3] = -((2.0 * zNear * zFar) / (zFar - zNear));
    m[3][2] = -1;
    m[3][3] = 0;
}

template <int rows, int cols, class T, int n, class Tv>
void scale(Matrix<cols, rows, T>& m, const Vector<n, Tv>& v) {
    static_assert(rows == cols, "Invalid matrix to scale.");
    static_assert(rows - 1 == n, "Invalid scale vector.");

    Matrix<cols, rows, T> transm;
    for (int i = 0; i + 1 < rows; ++i)
        transm[i][i] = v[i];

    m *= transm;
}

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
