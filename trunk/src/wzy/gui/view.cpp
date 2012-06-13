#include <wzy/gui/view.hpp>

#include <wzy/core/engine.hpp>
#include <wzy/render/render.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {
namespace gui {

View::View(const UDim& position,
           const UDim& size) :
    Object(position, size),
    mFB(new render::FrameBuffer(size.currentAbs())),
    mRenderData(render::Data::quad()),
    mMaterial(new Material) {

    mMaterial->textures()->push_back(mFB->colourAttachment(0));
}


// ------------------------------------
void View::draw(const UDim& position,
                const Vector2f& scale) {
    Object::draw(position, scale);

    mFB->bind();
    render::clear();

    Engine::singleton().rootNode()->draw(Engine::singleton().rootNode()->transformation());

    render::FrameBuffer::useDefault();

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
    print(midtrans);
    translate(mdlview, totranslate);

    auto toscale = Vector3f(sizeToDisplay, 1.0);
    wzy::scale(mdlview, toscale);

    mMaterial->use();
    mMaterial->program()->uniform("wzyProjectionMatrix", proj);
    mMaterial->program()->uniform("wzyModelViewMatrix", mdlview);
    mRenderData->draw();
}

}
}
