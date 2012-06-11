#include <wzy/gui/object.hpp>

namespace wzy {
namespace gui {

Object::Object(const UDim& position,
               const UDim& size) :
    mPosition(position),
    mSize(size),
    mScale(1.0, 1.0),
    mObjects() {
}


// -----------------------------------
void Object::draw(const UDim& position, const Vector2f& scale) {
    for (auto obj : mObjects)
        obj->draw(position + mPosition, scale + mScale);
}

}
}
