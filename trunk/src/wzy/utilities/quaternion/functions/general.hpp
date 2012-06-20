#ifndef WZY_UTILITIES_QUATERNION_FUNCTIONS_GENERAL_HPP
#define WZY_UTILITIES_QUATERNION_FUNCTIONS_GENERAL_HPP

#include <iostream>

#include <cmath>

#include <wzy/utilities/quaternion/operators/math.hpp>
#include <wzy/utilities/quaternion/quaternionfwd.hpp>
#include <wzy/utilities/mat.hpp>
#include <wzy/utilities/angle.hpp>


namespace wzy {

template <class T, class... Args>
void assign(Quaternion<T>& quat, const Radian& roll, const Radian& pitch, const Radian& yaw) {
    T sinRoll = std::sin(roll.v() / 2.0);
    T cosRoll = std::cos(roll.v() / 2.0);

    T sinPitch = std::sin(pitch.v() / 2.0);
    T cosPitch = std::cos(pitch.v() / 2.0);

    T sinYaw = std::sin(yaw.v() / 2.0);
    T cosYaw = std::cos(yaw.v() / 2.0);

    quat.setW(cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw);
    quat.setX(sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw);
    quat.setY(cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw);
    quat.setZ(cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw);

    normalise(quat);
}

template <class T, class Tv>
void assign(Quaternion<T>& quat, const Quaternion<Tv>& val) {
    quat.setW(val.w());
    quat.setX(val.x());
    quat.setY(val.y());
    quat.setZ(val.z());
}

template <class T>
void identity(Quaternion<T>& quat) {
    quat.setW(1.0);
    quat.setX(0.0);
    quat.setY(0.0);
    quat.setZ(0.0);
}

template <class T>
float magnitude(const Quaternion<T>& quat)
{ return std::sqrt(quat.w() * quat.w() + quat.x() * quat.x() + quat.y() * quat.y() + quat.z() * quat.z()); }

template <class T>
const Matrix3<T> getMatrix(const Quaternion<T>& quat) {
    return Matrix3<T>(
                1.0 - 2.0 * (quat.y() * quat.y() + quat.z() * quat.z()),
                2.0 * (quat.x() * quat.y() - quat.w() * quat.z()),
                2.0 * (quat.w() * quat.y() + quat.x() * quat.z()),

                2.0 * (quat.x() * quat.y() + quat.w() * quat.z()),
                1.0 - 2.0 * (quat.x() * quat.x() + quat.z() * quat.z()),
                2.0 * (quat.y() * quat.z() - quat.w() * quat.x()),

                2.0 * (quat.x() * quat.z() - quat.w() * quat.y()),
                2.0 * (quat.w() * quat.x() + quat.y() * quat.z()),
                1.0 - 2.0 * (quat.x() * quat.x() + quat.y() * quat.y())
                     );
}

template <class T>
void normalise(Quaternion<T>& quat)
{ quat /= magnitude(quat); }

template <class T>
void print(const Quaternion<T>& quat) {
    std::cout << quat.w() << ", " << quat.x() << ", " << quat.y() << ", " << quat.z() << std::endl;
}

template <int rows, int cols, class Tm, class Tq>
void rotate(Matrix<rows, cols, Tm>& m, const Quaternion<Tq>& quat) {
    m *= Matrix<rows, cols, Tm>(getMatrix(quat));
}

}

#endif
