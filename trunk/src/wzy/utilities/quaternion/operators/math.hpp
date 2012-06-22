#ifndef WZY_UTILITIES_QUATERNION_OPERATORS_MATH_HPP
#define WZY_UTILITIES_QUATERNION_OPERATORS_MATH_HPP

#include <utility>

#include <wzy/utilities/quaternion/quaternionfwd.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {

template <class Tlhs, class Trhs>
const Quaternion<decltype(std::declval<Tlhs>() * std::declval<Trhs>())>
operator*(const Quaternion<Tlhs>& lhs, const Quaternion<Trhs>& rhs) {
    Quaternion<decltype(std::declval<Tlhs>() * std::declval<Trhs>())> ret;
    ret.setW(lhs.w() * rhs.w() - lhs.x() * rhs.x() - lhs.y() * rhs.y() - lhs.z() * rhs.z());
    ret.setX(lhs.w() * rhs.x() + lhs.x() * rhs.w() + lhs.y() * rhs.z() - lhs.z() * rhs.y());
    ret.setY(lhs.w() * rhs.y() - lhs.x() * rhs.z() + lhs.y() * rhs.w() + lhs.z() * rhs.x());
    ret.setZ(lhs.w() * rhs.z() + lhs.x() * rhs.y() - lhs.y() * rhs.x() + lhs.z() * rhs.w());
    return ret;
}

template <class Tlhs, class Trhs>
const Vector3<Trhs> operator*(const Quaternion<Tlhs>& lhs, const Vector3<Trhs>& rhs) {
    Vector3<Trhs> v(rhs);
    normalise(v);
    Quaternion<Tlhs> vecQuat(0.0, v.x(), v.y(), v.z());
    vecQuat *= conjugate(lhs);
    vecQuat = lhs * vecQuat;
    return Vector3<Trhs>(vecQuat.x(), vecQuat.y(), vecQuat.z());
}



#define WZY_UTILITIES_QUATERNION_OPERATORS_MATH_DEFINE_OPASSIGNMENT(op) \
template <class Tlhs, class Trhs> \
Quaternion<Tlhs>& operator op##=(Quaternion<Tlhs>& lhs, const Quaternion<Trhs>& rhs) \
{ return lhs = lhs op rhs; } \
\
template <class Tq, class Trhs> \
Quaternion<Tq>& operator op##=(Quaternion<Tq>& quat, const Trhs& rhs) { \
    quat.setW(quat.w() op rhs); \
    quat.setX(quat.x() op rhs); \
    quat.setY(quat.y() op rhs); \
    quat.setZ(quat.z() op rhs); \
    return quat; \
}


WZY_UTILITIES_QUATERNION_OPERATORS_MATH_DEFINE_OPASSIGNMENT(+)
WZY_UTILITIES_QUATERNION_OPERATORS_MATH_DEFINE_OPASSIGNMENT(-)
WZY_UTILITIES_QUATERNION_OPERATORS_MATH_DEFINE_OPASSIGNMENT(*)
WZY_UTILITIES_QUATERNION_OPERATORS_MATH_DEFINE_OPASSIGNMENT(/)

}

#endif
