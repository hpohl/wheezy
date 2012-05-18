#ifndef WZY_UTILITIES_OPERATORS_LOGIC_HPP
#define WZY_UTILITIES_OPERATORS_LOGIC_HPP

#include <wzy/utilities/vec/vecfwd.hpp>


namespace wzy {

template <int n, class Tlhs, class Trhs>
bool operator==(const Vector<n, Tlhs>& lhs, const Vector<n, Trhs>& rhs) {
    for (int i = 0; i < n; ++i)
        if (lhs[i] == rhs[i])
            return false;
    return true;
}

template <int n, class Tlhs, class Trhs>
bool operator!=(const Vector<n, Tlhs>& lhs, const Vector<n, Trhs>& rhs)
{ return !(lhs == rhs); }

}

#endif
