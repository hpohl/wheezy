#include <wzy/gui/image.hpp>


namespace wzy {
namespace gui {

Image::Image(const UDim& position,
             const UDim& size,
             const std::shared_ptr<render::Texture2D>& texture) :
    Object(position, size),
    mRenderData(render::Data::quad()),
    mMaterial(new Material) {

    mMaterial->textures()->push_back(texture);
}

Image::~Image() {
}


// ----------------------------------
void Image::draw(const UDim& position, const Vector2f& scale) {
    Matrix4f proj;
    orthographic(proj, 0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    Matrix4f mdlview;

    auto sizeToDisplay = scale * this->scale() * size().currentRel();
    auto midtrans = Vector3f((sizeToDisplay / Vector2f(2.0, 2.0)).x(),
                             (sizeToDisplay / Vector2f(2.0, 2.0)).y(),
                             0.0);
    auto postrans = Vector3f((position + this->position()).currentRel(), 0.0);
    auto totranslate = midtrans + postrans;
    totranslate = Vector3f(totranslate.x(), 1.0 - totranslate.y(), totranslate.z());
    translate(mdlview, totranslate);

    auto toscale = Vector3f(sizeToDisplay, 1.0);
    wzy::scale(mdlview, toscale);

    mMaterial->use();
    mMaterial->program()->uniform("wzyProjectionMatrix", proj);
    mMaterial->program()->uniform("wzyModelViewMatrix", mdlview);
    mRenderData->draw();

    Object::draw(position, scale);
}

void Image::setTexture(const std::shared_ptr<render::Texture2D>& texture) {
    mMaterial->textures()->at(0) = texture;
}

}
}
