#ifndef WZY_UTILITIES_VEC_ALIASES_HPP
#define WZY_UTILITIES_VEC_ALIASES_HPP

#include <wzy/utilities/vec/vecfwd.hpp>


namespace wzy {

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

template <int N>
using Vectorc = Vector<N, char>;

template <int N>
using Vectoruc = Vector<N, unsigned char>;


// Typedefs
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2ui;

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
typedef Vector3<int> Vector3i;

typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;
typedef Vector4<int> Vector4i;
typedef Vector4<unsigned char> Vector4uc;

}

#endif
