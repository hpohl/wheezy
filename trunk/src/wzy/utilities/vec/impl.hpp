#ifndef WZY_UTILITIES_VEC_IMPL_HPP
#define WZY_UTILITIES_VEC_IMPL_HPP

#include <wzy/utilities/vec/vecfwd.hpp>


namespace wzy {

namespace detail {
namespace vec {

template <int n, class T, int idx>
struct AccessImpl {
};

template <int n, class T>
struct AccessImpl<n, T, 0> {
    const T x() const
    { return static_cast<const Vector<n, T>&>(*this)[0]; }

    void setX(const T& x)
    { static_cast<Vector<n, T>&>(*this)[0] = x; }

    const T width() const
    { return static_cast<const Vector<n, T>&>(*this)[0]; }
};

template <int n, class T>
struct AccessImpl<n, T, 1> : public AccessImpl<n, T, 0> {
    const T y() const
    { return static_cast<const Vector<n, T>&>(*this)[1]; }

    void setY(const T& y)
    { static_cast<Vector<n, T>&>(*this)[1] = y; }

    const T height() const
    { return static_cast<const Vector<n, T>&>(*this)[1]; }
};

template <int n, class T>
struct AccessImpl<n, T, 2> : public AccessImpl<n, T, 1> {
    const T z() const
    { return static_cast<const Vector<n, T>&>(*this)[2]; }
};

template <int n, class T>
struct AccessImpl<n, T, 3> : public AccessImpl<n, T, 2> {
    const T w() const
    { return static_cast<const Vector<n, T>&>(*this)[3]; }
};

}
}

}

#endif
