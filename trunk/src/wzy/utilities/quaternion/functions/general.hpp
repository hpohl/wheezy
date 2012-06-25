#ifndef WZY_UTILITIES_QUATERNION_FUNCTIONS_GENERAL_HPP
#define WZY_UTILITIES_QUATERNION_FUNCTIONS_GENERAL_HPP

#include <iostream>

#include <cmath>

#include <wzy/utilities/quaternion/operators/math.hpp>
#include <wzy/utilities/quaternion/quaternionfwd.hpp>
#include <wzy/utilities/mat.hpp>
#include <wzy/utilities/angle.hpp>


namespace wzy {

template <class T, class TW, class TX, class TY, class TZ>
void assign(Quaternion<T>& quat, const TW& w, const TX& x, const TY& y, const TZ& z) {
    quat.setW(w);
    quat.setX(x);
    quat.setY(y);
    quat.setZ(z);
}

template <class T>
void assign(Quaternion<T>& quat, const Vector3f& axis, const Radian& angle) {
    double sinA = std::sin(angle.v());
    double cosA = std::cos(angle.v());

    quat.setW(cosA);
    quat.setX(axis.x() * sinA);
    quat.setY(axis.y() * sinA);
    quat.setZ(axis.z() * sinA);
}

template <class T>
void assign(Quaternion<T>& quat, const Radian& roll, const Radian& pitch, const Radian& yaw) {
    double angle = roll.v() * 0.5;
    double sr = std::sin(angle);
    double cr = std::cos(angle);

    angle = pitch.v() * 0.5;
    double sp = std::sin(angle);
    double cp = std::cos(angle);

    angle = yaw.v() * 0.5;
    double sy = std::sin(angle);
    double cy = std::cos(angle);

    double cpcy = cp * cy;
    double spcy = sp * cy;
    double cpsy = cp * sy;
    double spsy = sp * sy;

    quat.setW(cr * cpcy + sr * spsy);
    quat.setX(sr * cpcy - cr * spsy);
    quat.setY(cr * spcy + sr * cpsy);
    quat.setZ(cr * cpsy - sr * spcy);

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
void print(const Quaternion<T>& quat) {
    std::cout << quat.w() << ", " << quat.x() << ", " << quat.y() << ", " << quat.z() << std::endl;
}

}

#endif
