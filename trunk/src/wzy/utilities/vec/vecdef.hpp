#ifndef WZY_UTILITIES_VEC_VECDEF_HPP
#define WZY_UTILITIES_VEC_VECDEF_HPP

#include <type_traits>
#include <utility>

#include <cassert>
#include <cstddef>

#include <wzy/utilities/vec/functions/general.hpp>
#include <wzy/utilities/vec/functions/math.hpp>
#include <wzy/utilities/vec/operators/logic.hpp>
#include <wzy/utilities/vec/operators/math.hpp>
#include <wzy/utilities/vec/aliases.hpp>
#include <wzy/utilities/vec/impl.hpp>


namespace wzy {

namespace detail {
namespace vec {
struct BaseVec { };
}
}

template <int n, class T>
class Vector : public detail::vec::BaseVec, public detail::vec::AccessImpl<n, T, n - 1> {
public:
    Vector() :
        mData {0} { }

    template <class... Args>
    Vector(Args&&... args)
    { wzy::assign(*this, std::forward<Args>(args)...); }


    // -----------------------------------------------
    T& operator[](size_t i)
    { assert(i < n); return mData[i]; }

    const T& operator[](size_t i) const
    { assert(i < n); return mData[i]; }


    // --------------------------------------
    T* data()
    { return mData; }

private:
    T mData[n];
};

}

#endif
