#include <wzy/scene/movable.hpp>

namespace wzy {

Movable::~Movable() {
}


// ------------------------------
const Matrix4f Movable::transformation() const {
    Matrix4f m;
    wzy::translate(m, mPosition);
    wzy::scale(m, mScale);
    return m;
}

}
