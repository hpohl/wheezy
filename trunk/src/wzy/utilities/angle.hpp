#ifndef WZY_UTILITIES_ANGLE_HPP
#define WZY_UTILITIES_ANGLE_HPP

#include <wzy/utilities/general.hpp>


namespace wzy {

class Degree;
class Radian;

class Degree {
public:
    explicit Degree(float value) :
        mValue(value) { }

    inline Degree(const Radian& rad);

    inline Degree& operator=(const Radian& rad);

    float v() const
    { return mValue; }

    inline const Radian toRadian() const;

private:
    float mValue;
};

class Radian {
public:
    explicit Radian(float value) :
        mValue(value) { }

    inline Radian(const Degree& deg);

    inline Radian& operator=(const Degree& deg);

    float v() const
    { return mValue; }

    inline const Degree toDegree() const;

private:
    float mValue;
};


// ------------------------------------------------------------
#define WZY_UTILITIES_ANGLE_DEFINE_BINARY_OPERATOR(c, op) \
inline const c operator op(const c& lhs, const c& rhs) \
{ return c(lhs.v() op rhs.v()); } \
\
template <class T> \
inline const c operator op(const c& lhs, const T& rhs) \
{ return c(lhs.v() op rhs); } \
 \
template <class T> \
inline const c operator op(const T& lhs, const c& rhs) \
{ return c(lhs op rhs.v()); }

#define WZY_UTILITIES_ANGLE_DEFINE_UNARY_OPERATOR(c, op) \
inline const c operator op(const c& val) \
{ return c(-val.v()); }


// ---------------------------------------------------------
Degree::Degree(const Radian& rad) :
    mValue(rad.toDegree().v()) { }

Degree& Degree::operator=(const Radian& rad)
{ mValue = rad.toDegree().v(); return *this; }

#define WZY_UTILITIES_ANGLE_DEGREE_DEFINE_BINARY_OPERATOR(op) \
    WZY_UTILITIES_ANGLE_DEFINE_BINARY_OPERATOR(Degree, op)

WZY_UTILITIES_ANGLE_DEGREE_DEFINE_BINARY_OPERATOR(+)
WZY_UTILITIES_ANGLE_DEGREE_DEFINE_BINARY_OPERATOR(-)
WZY_UTILITIES_ANGLE_DEGREE_DEFINE_BINARY_OPERATOR(*)
WZY_UTILITIES_ANGLE_DEGREE_DEFINE_BINARY_OPERATOR(/)

#define WZY_UTILITIES_ANGLE_DEGREE_DEFINE_UNARY_OPERATOR(op) \
    WZY_UTILITIES_ANGLE_DEFINE_UNARY_OPERATOR(Degree, op)

WZY_UTILITIES_ANGLE_DEGREE_DEFINE_UNARY_OPERATOR(+)
WZY_UTILITIES_ANGLE_DEGREE_DEFINE_UNARY_OPERATOR(-)

const Radian Degree::toRadian() const
{ return Radian(degreesToRadians(mValue)); }


// ----------------------------------------------------------
Radian::Radian(const Degree& deg) :
    mValue(deg.toRadian().v()) { }

Radian& Radian::operator=(const Degree& deg)
{ mValue = deg.toRadian().v(); return *this; }

#define WZY_UTILITIES_ANGLE_RADIAN_DEFINE_BINARY_OPERATOR(op) \
    WZY_UTILITIES_ANGLE_DEFINE_BINARY_OPERATOR(Radian, op)

WZY_UTILITIES_ANGLE_RADIAN_DEFINE_BINARY_OPERATOR(+)
WZY_UTILITIES_ANGLE_RADIAN_DEFINE_BINARY_OPERATOR(-)
WZY_UTILITIES_ANGLE_RADIAN_DEFINE_BINARY_OPERATOR(*)
WZY_UTILITIES_ANGLE_RADIAN_DEFINE_BINARY_OPERATOR(/)

#define WZY_UTILITIES_ANGLE_RADIAN_DEFINE_UNARY_OPERATOR(op) \
    WZY_UTILITIES_ANGLE_DEFINE_UNARY_OPERATOR(Radian, op)

WZY_UTILITIES_ANGLE_RADIAN_DEFINE_UNARY_OPERATOR(+)
WZY_UTILITIES_ANGLE_RADIAN_DEFINE_UNARY_OPERATOR(-)

const Degree Radian::toDegree() const
{ return Degree(radiansToDegrees(mValue)); }


// ------------------------------------------------------
#define WZY_UTILITIES_ANGLE_DEFINE_UNIVERSAL_BINARY_OPERATOR(op) \
inline const Radian operator op(const Radian& rad, const Degree& deg) \
{ return Radian(rad.v() op deg.toRadian().v()); }

WZY_UTILITIES_ANGLE_DEFINE_UNIVERSAL_BINARY_OPERATOR(+)
WZY_UTILITIES_ANGLE_DEFINE_UNIVERSAL_BINARY_OPERATOR(-)
WZY_UTILITIES_ANGLE_DEFINE_UNIVERSAL_BINARY_OPERATOR(*)
WZY_UTILITIES_ANGLE_DEFINE_UNIVERSAL_BINARY_OPERATOR(/)

}


#endif
