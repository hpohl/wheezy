#include <wzy/utilities/mat.hpp>


int main() {
    wzy::Matrix3f m(1, 2, 3,
                    4, 5, 6,
                    7, 8, 9);

    wzy::Matrix3f n(m);

    wzy::print(m * n);
    std::cout << std::endl;
    wzy::print(n);

    return 0;
}
