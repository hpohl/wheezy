#include <wzy/gui/view.hpp>

#include <wzy/core/engine.hpp>
#include <wzy/render/render.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {
namespace gui {

View::View(const UDim& position,
           const UDim& size,
           const Vector2i& frameBufferSize) :
    Image(position, size),
    mFB(new render::FrameBuffer(frameBufferSize == Vector2i(0, 0) ? size.currentAbs() : frameBufferSize)),
    mCamera(new Camera) {

    setTexture(mFB->colourAttachment(0));
}


// ------------------------------------
void View::draw(const UDim& position,
                const Vector2f& scale) {
    render::FrameBuffer::Pusher pusher(mFB);

    Matrix4f transf;
    translate(transf, -camera()->position());

    render::clear();
    Engine::singleton().rootNode()->draw(camera()->projection(), transf);

    pusher.pop();

    Image::draw(position, scale);
}

}
}
