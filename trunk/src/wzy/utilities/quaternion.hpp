#ifndef WZY_UTILITIES_QUATERNION_HPP
#define WZY_UTILITIES_QUATERNION_HPP

#include <wzy/utilities/general.hpp>
#include <wzy/utilities/mat.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {

class Degree;
class Radian;


class Degree {
public:
    explicit Degree(float val = 0.0) :
        mVal(val) { }

    inline Degree(const Radian& rad);


    operator float() const
    { return mVal; }

private:
    float mVal;
};

class Radian {
public:
    explicit Radian(float val = 0.0) :
        mVal(val) { }

    inline Radian(const Degree& deg);


    operator float() const
    { return mVal; }

private:
    float mVal;
};


Degree::Degree(const Radian& rad) :
    mVal(radiansToDegrees<float>(rad)) { }

Radian::Radian(const Degree& deg) :
    mVal(degreesToRadians<float>(deg)) { }


// ----------------------------------------------
class Quaternion {
public:
    explicit Quaternion(float w = 1.0, const Vector3f& rot = Vector3f(0.0, 0.0, 0.0)) :
        mVec(w, rot) { }

    explicit Quaternion(const Radian& angle, const Vector3f& axis) {

    }

    Quaternion(const Quaternion& other) :
        mVec(other.mVec) { }


    float& operator[](size_t idx)
    { return mVec[idx]; }

    const float& operator[](size_t idx) const
    { return mVec[idx]; }

    Radian yaw() const {
        float x  = 2.0f * mX;
        float y  = 2.0f * mY;
        float z  = 2.0f * mZ;
        float wy = y * mW;
        float xx = x * mX;
        float xz = z * mX;
        float yy = y * mY;

        return Radian(std::atan2(xz + wy, 1.0 - (xx + yy)));
    }

    Radian pitch() const {
        float x  = 2.0f * mX;
//      float y  = 2.0f * mY;
        float z  = 2.0f * mZ;
        float wx = x * mW;
        float xx = x * mX;
        float yz = z * mY;
        float zz = z * mZ;

        return Radian(std::atan2(yz + wx, 1.0 - (xx + zz)));
    }

private:
    union {
        Vector4f mVec;
        float mW, mX, mY, mZ;
    };
};

}

#endif
