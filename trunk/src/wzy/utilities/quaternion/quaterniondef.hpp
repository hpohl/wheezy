#ifndef WZY_UTILITIES_QUATERNION_QUATERNIONDEF_HPP
#define WZY_UTILITIES_QUATERNION_QUATERNIONDEF_HPP

#include <wzy/utilities/quaternion/functions/general.hpp>
#include <wzy/utilities/quaternion/functions/math.hpp>
#include <wzy/utilities/quaternion/operators/math.hpp>
#include <wzy/utilities/quaternion/aliases.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {

template <class T>
class Quaternion {
public:
    Quaternion()
    { identity(*this); }

    template <class... Args>
    Quaternion(Args&&... args)
    { assign(*this, std::forward<Args>(args)...); }

    const T w() const
    { return mW; }

    const T x() const
    { return mX; }

    const T y() const
    { return mY; }

    const T z() const
    { return mZ; }

    void setW(const T& w)
    { mW = w; }

    void setX(const T& x)
    { mX = x; }

    void setY(const T& y)
    { mY = y; }

    void setZ(const T& z)
    { mZ = z; }

    const Radian roll() const
    { return Radian(std::atan2(2.0 * (mW * mX + mY * mZ), 1.0 - 2.0 * (mX * mX + mY * mY))); }

    const Radian pitch() const
    { return Radian(std::asin(2.0 * (mW * mY - mZ * mX))); }

    const Radian yaw() const
    { return Radian(std::atan2(2.0 * (mW * mZ + mX * mY), 1.0 - 2.0 * (mY * mY + mZ * mZ))); }

    void setRoll(const Radian& roll)
    { (*this) *= Quaternion(Radian(-this->roll() + roll), Radian(0.0), Radian(0.0)); }

    void setPitch(const Radian& pitch)
    { (*this) *= Quaternion(Radian(0.0), Radian(-this->pitch() + pitch), Radian(0.0)); }

    void setYaw(const Radian& yaw)
    { (*this) *= Quaternion(Radian(0.0), Radian(0.0), Radian(-this->yaw() + yaw)); }


private:
    T mW, mX, mY, mZ;
};

}

#endif
