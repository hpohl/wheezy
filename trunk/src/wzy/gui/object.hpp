#ifndef WZY_GUI_OBJECT_HPP
#define WZY_GUI_OBJECT_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include <wzy/gui/udim.hpp>
#include <wzy/render/framebuffer.hpp>


namespace wzy {
namespace gui {

class Object {
public:
    Object(const UDim& position,
           const UDim& size);
    virtual ~Object() { }

    void attach(const std::shared_ptr<Object>& obj)
    { mObjects.push_back(obj); }

    void detach(const std::shared_ptr<Object>& obj)
    { std::remove(mObjects.begin(), mObjects.end(), obj); }

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
    std::vector<std::shared_ptr<Object> > mObjects;
};

}
}

#endif
