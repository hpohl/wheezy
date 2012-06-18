#include <wzy/scene/camera.hpp>


namespace wzy {

Camera::Camera() :
    AbstractSceneNode(),
    mFovY(60.0),
    mZNear(0.1),
    mZFar(100.0),
    mAspect(1.0) {
}


// -----------------------------
const Matrix4f Camera::projection() const {
    Matrix4f m;
    perspective(m, fovY(), aspect(), zNear(), zFar());
    return m;
}

}
