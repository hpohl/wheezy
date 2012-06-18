#ifndef WZY_SCENE_MOVEABLE_HPP
#define WZY_SCENE_MOVEABLE_HPP

#include <wzy/utilities/mat.hpp>
#include <wzy/utilities/quaternion.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {

class Movable {
public:
    Movable(const Vector3f& position = Vector3f(0.0, 0.0, 0.0),
            const Vector3f& scale = Vector3f(1.0, 1.0, 1.0)) :
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

    const Quaternion rotation() const
    { return mRotation; }

    void setRotation(const Quaternion& rot)
    { mRotation = rot; }


    const Matrix4f transformation() const;

private:
    Vector3f mPosition;
    Vector3f mScale;
    Quaternion mRotation;
};

}

#endif
