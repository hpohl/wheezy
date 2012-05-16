#ifndef WZY_UTILTIES_MAT_HPP
#define WZY_UTILTIES_MAT_HPP

#include <wzy/utilities/matdef.hpp>

namespace wzy {

extern template class Matrix<2, 2, float>;
extern template class Matrix<2, 2, double>;
extern template class Matrix<2, 2, int>;

extern template class Matrix<3, 3, float>;
extern template class Matrix<3, 3, double>;
extern template class Matrix<3, 3, int>;

extern template class Matrix<4, 4, float>;
extern template class Matrix<4, 4, double>;
extern template class Matrix<4, 4, int>;

}

#endif
