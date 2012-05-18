#include <wzy/scene/movable.hpp>

namespace wzy {

Movable::~Movable() {
}


// ------------------------------
const Matrix4f Movable::transform() const {
    Matrix4f m;
    m.translate(mPosition);
    return m;
}

}
