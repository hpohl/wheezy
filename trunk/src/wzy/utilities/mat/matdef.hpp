#ifndef WZY_UTILITIES_MAT_MATDEF_HPP
#define WZY_UTILITIES_MAT_MATDEF_HPP

#include <utility>

#include <cassert>

#include <wzy/utilities/mat/functions/general.hpp>
#include <wzy/utilities/mat/functions/math.hpp>
#include <wzy/utilities/mat/operators/math.hpp>
#include <wzy/utilities/mat/aliases.hpp>
#include <wzy/utilities/tmp.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {

namespace detail {
namespace mat {
struct MatID { };
}
}

template <int rows, int cols, class T>
class Matrix : public detail::mat::MatID {
public:
    static_assert(rows > 1 && cols > 1, "A matrix has to have at least 2 rows and cols.");

    struct GetIniter {
        struct Identity {
            template <int n, class Tm>
            static void go(Matrix<n, n, Tm>& m)
            { identity(m); }
        };

        struct Zero {
            template <int r, int c, class Tm>
            static void go(Matrix<r, c, Tm>& m)
            { zero(m); }
        };

        typedef typename std::conditional<rows == cols, Identity, Zero>::type type;
    };

    Matrix()
    { GetIniter::type::go(*this); }

    template <class... Args>
    Matrix(Args&&... args)
    { assign(*this, std::forward<Args>(args)...); }

    template <class... Args>
    Matrix& operator=(Args&&... args)
    { assign(*this, std::forward<Args>(args)...); return *this; }


    Vector<rows, T>& operator[](std::size_t i)
    { assert(i < rows); return mData[i]; }

    const Vector<rows, T>& operator[](std::size_t i) const
    { assert(i < rows); return mData[i]; }

    const T* data() const
    { return reinterpret_cast<const T*>(mData); }

private:
    Vector<cols, T> mData[rows];
};

}

#endif
