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
    mFB(new render::FrameBuffer(size.current())),
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
    orthographic(proj, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    Matrix4f mdlview;
    wzy::scale(mdlview, Vector3f(Vector2f(2.0, 2.0) * scale * this->scale(), 1.0));
    translate(mdlview, Vector3f((this->position() + position).current() /
                                Vector2f(render::FrameBuffer::currentSize()), 0.0));

    mMaterial->use();
    mMaterial->program()->uniform("wzyProjectionMatrix", proj);
    mMaterial->program()->uniform("wzyModelViewMatrix", mdlview);
    mRenderData->draw();
}

}
}
