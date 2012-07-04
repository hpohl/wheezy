#ifndef WZY_GUI_VIEW_HPP
#define WZY_GUI_VIEW_HPP

#include <wzy/gui/image.hpp>


namespace wzy {

class Camera;
class AbstractSceneNode;

namespace render {
class FrameBuffer;
}

namespace gui {

class View : public Image {
public:
    View(const std::shared_ptr<AbstractSceneNode>& node,
         const UDim& position,
         const UDim& size,
         const Vector2i& frameBufferSize = Vector2i(0, 0));

    void draw(const UDim& position, const Vector2f& scale) override;

    const std::shared_ptr<Camera> camera()
    { return mCamera; }

private:
    std::shared_ptr<AbstractSceneNode> mSceneNode;
    std::shared_ptr<render::FrameBuffer> mFB;
    std::shared_ptr<Camera> mCamera;
};

}
}

#endif
