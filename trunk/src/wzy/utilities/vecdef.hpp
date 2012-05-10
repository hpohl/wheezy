#ifndef WZY_UTIL_VECDEF_HPP
#define WZY_UTIL_VECDEF_HPP

#include <cassert>
#include <cstddef>


namespace wzy {

template <int n, class T>
class Vector;

namespace detail {
namespace vec {

template <int n, class T, int idx>
struct AccessImpl {
};

template <int n, class T>
struct AccessImpl<n, T, 0> {
    const T x() const
    { return static_cast<const Vector<n, T>&>(*this)[0]; }

    const T width() const
    { return static_cast<const Vector<n, T>&>(*this)[0]; }
};

template <int n, class T>
struct AccessImpl<n, T, 1> : public AccessImpl<n, T, 0> {
    const T y() const
    { return static_cast<const Vector<n, T>&>(*this)[1]; }

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

template <int n, class T>
class Vector : public detail::vec::AccessImpl<n, T, n - 1> {
public:
    template <class... Args>
    Vector(Args&&... args) :
        mData {static_cast<T>(args)...} { }


    // -----------------------------------------------
    T& operator[](size_t i)
    { assert(i < n); return mData[i]; }

    const T& operator[](size_t i) const
    { assert(i < n); return mData[i]; }

private:
    T mData[n];
};


// Template aliases
template <class T>
using Vector2 = Vector<2, T>;

template <class T>
using Vector3 = Vector<3, T>;

template <class T>
using Vector4 = Vector<4, T>;


template <int N>
using Vectorf = Vector<N, float>;

template <int N>
using Vectord = Vector<N, double>;

template <int N>
using Vectori = Vector<N, int>;


// Typedefs
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
typedef Vector3<int> Vector3i;

typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;
typedef Vector4<int> Vector4i;

}

#endif
