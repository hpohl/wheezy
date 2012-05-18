#ifndef WZY_UTILITIES_HELPERS_ASSIGN_HPP
#define WZY_UTILITIES_HELPERS_ASSIGN_HPP

namespace wzy {

template <int n, class Tlhs, class Trhs>
void assign(Tlhs& lhs, const Trhs& rhs) {
    for (int i = 0; i < n; ++i)
        lhs[i] = rhs[i];
}

}

#endif
