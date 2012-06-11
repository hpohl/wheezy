#ifndef WZY_GUI_VIEW_HPP
#define WZY_GUI_VIEW_HPP

#include <memory>

#include <wzy/gui/object.hpp>
#include <wzy/render/data.hpp>
#include <wzy/render/framebuffer.hpp>
#include <wzy/scene/material.hpp>


namespace wzy {

namespace gui {

class View : public Object {
public:
    View(const UDim& position,
         const UDim& size);

    void draw(const UDim& position,
              const Vector2f& scale) override;

private:
    std::shared_ptr<render::FrameBuffer> mFB;
    std::shared_ptr<render::Data> mRenderData;
    std::shared_ptr<Material> mMaterial;
};

}
}

#endif
