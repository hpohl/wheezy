#ifndef WZY_GUI_IMAGE_HPP
#define WZY_GUI_IMAGE_HPP

#include <wzy/gui/object.hpp>
#include <wzy/render/data.hpp>
#include <wzy/scene/material.hpp>


namespace wzy {
namespace gui {

class Image : public Object {
public:
    Image(const UDim& position,
          const UDim& size,
          const std::shared_ptr<render::Texture2D>& texture = std::make_shared<render::Texture2D>());

    ~Image();


    void draw(const UDim& position,
              const Vector2f& scale) override;

    const std::shared_ptr<render::Texture2D> texture()
    { return mMaterial->textures()->at(0); }

    void setTexture(const std::shared_ptr<render::Texture2D>& texture);


private:
    std::shared_ptr<render::Data> mRenderData;
    std::shared_ptr<Material> mMaterial;
};

}
}

#endif
