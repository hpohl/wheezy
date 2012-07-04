#ifndef WZY_GUI_OBJECT_HPP
#define WZY_GUI_OBJECT_HPP

#include <memory>
#include <set>

#include <wzy/gui/udim.hpp>


namespace wzy {
namespace gui {

class Object {
public:
    Object(const UDim& position,
           const UDim& size);
    virtual ~Object() { }

    void attach(const std::shared_ptr<Object>& obj);
    void detach(const std::shared_ptr<Object>& obj);

    virtual void draw(const UDim& position,
                      const Vector2f& scale);

    const UDim position() const
    { return mPosition; }

    void move(const UDim& position)
    { mPosition = position; }

    const UDim size() const
    { return mSize; }

    void resize(const UDim& size)
    { mSize = size; }

    const Vector2f scale() const
    { return mScale; }

    void scale(const Vector2f& scale)
    { mScale = scale; }

private:
    UDim mPosition;
    UDim mSize;
    Vector2f mScale;
    std::set<std::shared_ptr<Object> > mObjects;
};

}
}

#endif
