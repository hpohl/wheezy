#ifndef WZY_SCENE_CAMERA_HPP
#define WZY_SCENE_CAMERA_HPP

#include <wzy/scene/node.hpp>


namespace wzy {

class Camera : public AbstractSceneNode {
public:
    Camera();

    float fovY() const
    { return mFovY; }

    void setFovY(float fovY)
    { mFovY = fovY; }

    float zNear() const
    { return mZNear; }

    float zFar() const
    { return mZFar; }

    float aspect() const
    { return mAspect; }

private:
    float mFovY;
    float mZNear, mZFar;
    float mAspect;
};

}

#endif
