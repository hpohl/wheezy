#ifndef WZY_UTILITIES_HELPERS_OPERATIONS_HPP
#define WZY_UTILITIES_HELPERS_OPERATIONS_HPP

namespace wzy {
namespace op {

#define WZY_UTILITIES_HELPERS_DEFINE_OPERATION(name, op) \
struct name { \
    template <class Tlhs, class Trhs> \
    static auto go(Tlhs&& lhs, Trhs&& rhs) -> decltype(lhs op rhs) \
    { return lhs op rhs; } \
};

WZY_UTILITIES_HELPERS_DEFINE_OPERATION(Plus, +);
WZY_UTILITIES_HELPERS_DEFINE_OPERATION(Minus, -);
WZY_UTILITIES_HELPERS_DEFINE_OPERATION(Multiply, *);
WZY_UTILITIES_HELPERS_DEFINE_OPERATION(Divide, /);
WZY_UTILITIES_HELPERS_DEFINE_OPERATION(Modulo, %);

//WZY_UTILITIES_HELPERS_DEFINE_OPERATION(Assign, =);

struct Assign {
    template <class Tlhs, class Trhs>
    static auto go(Tlhs& lhs, const Trhs& rhs) -> decltype(lhs = rhs)
    { return lhs = rhs; }
};

}

template <class Op, class Tlhs, class Trhs>
auto operate(Tlhs&& lhs, Trhs&& rhs) -> decltype(Op::go(lhs, rhs))
{ return Op::go(lhs, rhs); }

template <class Op, int n, class Tlhs, class Trhs>
void operate(Tlhs&& lhs, Trhs&& rhs)
{ for (int i = 0; i < n; ++i) Op::go(lhs[i], rhs[i]); }

template <class Op, int n, class Tlhs, class Trhs, class Tres>
void operate(Tlhs&& lhs, Trhs&& rhs, Tres&& res)
{ for (int i = 0; i < n; ++i) res[i] = Op::go(lhs[i], rhs[i]); }

}

#endif
