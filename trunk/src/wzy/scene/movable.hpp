#ifndef WZY_SCENE_MOVEABLE_HPP
#define WZY_SCENE_MOVEABLE_HPP

#include <wzy/utilities/vec.hpp>


namespace wzy {

class Movable {
public:
    Movable(const Vector3f& position = Vector3f()) :
        mPosition(position) { }
    virtual ~Movable() = 0;

    const Vector3f positon() const
    { return mPosition; }

    void setPosition(const Vector3f& position)
    { mPosition = position; }

private:
    Vector3f mPosition;
};

}

#endif
