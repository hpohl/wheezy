#include <wzy/scene/camera.hpp>

namespace wzy {

Camera::Camera() :
    AbstractSceneNode(),
    mFovY(60.0),
    mZNear(0.1),
    mZFar(100.0) {
}

}
