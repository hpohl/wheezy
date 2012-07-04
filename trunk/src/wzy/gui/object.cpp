#include <wzy/gui/object.hpp>

#include <wzy/utilities/exception.hpp>
#include <wzy/utilities/general.hpp>


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
        obj->draw(position + this->position(), scale * this->scale());
}

void Object::attach(const std::shared_ptr<Object>& obj) {
    if (!mObjects.insert(validate(obj)).second)
        throw Exception("Unable to attach GUI object.");
}

void Object::detach(const std::shared_ptr<Object>& obj) {
    if (mObjects.erase(obj) < 1)
        throw Exception("Failed to detach GUI object.");
}

}
}
