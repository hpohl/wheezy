#ifndef WZY_GUI_VIEW_HPP
#define WZY_GUI_VIEW_HPP

#include <wzy/gui/image.hpp>
#include <wzy/render/framebuffer.hpp>


namespace wzy {

namespace gui {

class View : public Image {
public:
    View(const UDim& position,
         const UDim& size);

    void draw(const UDim& position,
              const Vector2f& scale) override;

private:
    std::shared_ptr<render::FrameBuffer> mFB;
};

}
}

#endif
