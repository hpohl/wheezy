#ifndef WZY_UTILITIES_TMP_HPP
#define WZY_UTILITIES_TMP_HPP

namespace wzy {
namespace tmp {

template <int n1, int n2>
struct Highest {
    constexpr static int value = n1 > n2 ? n1 : n2;
};

template <int n1, int n2>
struct Lowest {
    constexpr static int value = n1 < n2 ? n1 : n2;
};

}
}

#endif
