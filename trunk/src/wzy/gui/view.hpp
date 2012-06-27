#ifndef WZY_GUI_VIEW_HPP
#define WZY_GUI_VIEW_HPP

#include <wzy/gui/image.hpp>
#include <wzy/render/framebuffer.hpp>
#include <wzy/scene/camera.hpp>
#include <wzy/scene/node.hpp>


namespace wzy {

namespace gui {

class View : public Image {
public:
    View(const std::shared_ptr<AbstractSceneNode>& node,
         const UDim& position,
         const UDim& size,
         const Vector2i& frameBufferSize = Vector2i(0, 0));

    void draw(const UDim& position,
              const Vector2f& scale) override;

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
