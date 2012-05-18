#ifndef WZY_SCENE_MOVEABLE_HPP
#define WZY_SCENE_MOVEABLE_HPP

#include <wzy/utilities/mat.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {

class Movable {
public:
    Movable(const Vector3f& position = Vector3f(),
            const Vector3f& scale = Vector3f()) :
        mPosition(position),
        mScale(scale) { }

    virtual ~Movable() = 0;

    const Vector3f position() const
    { return mPosition; }

    void setPosition(const Vector3f& position)
    { mPosition = position; }

    const Vector3f scale() const
    { return mScale; }

    void setScale(const Vector3f& scale)
    { mScale = scale; }


    const Matrix4f transform() const;

private:
    Vector3f mPosition;
    Vector3f mScale;
};

}

#endif
