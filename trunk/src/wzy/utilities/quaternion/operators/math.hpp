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
    ret.setX(lhs.w() * rhs.x()  +  lhs.x() * rhs.w()  +  lhs.y() * rhs.z()  -  lhs.z() * rhs.y());
    ret.setY(lhs.w() * rhs.y()  +  lhs.y() * rhs.w()  +  lhs.z() * rhs.x()  -  lhs.x() * rhs.z());
    ret.setZ(lhs.w() * rhs.z()  +  lhs.z() * rhs.w()  +  lhs.x() * rhs.y()  -  lhs.y() * rhs.x());
    ret.setW(lhs.w() * rhs.w()  -  lhs.x() * rhs.x()  -  lhs.y() * rhs.y()  -  lhs.z() * rhs.z());

    return ret;
}

template <class Tlhs, class Trhs>
const Vector3<Trhs> operator*(const Quaternion<Tlhs>& lhs, const Vector3<Trhs>& rhs) {
    Vector3<Trhs> qvec(lhs.x(), lhs.y(), lhs.z());
    Vector3<Trhs> uv(cross(qvec, rhs));
    Vector3<Trhs> uuv(cross(qvec, uv));
    uv *= 2.0 * lhs.w();
    uuv *= 2.0;
    return rhs + uv + uuv;
}

template <class Tlhs, class Trhs>
const Vector3<Tlhs> operator*(const Vector3<Tlhs>& lhs, const Quaternion<Trhs>& rhs)
{ return rhs * lhs; }



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
