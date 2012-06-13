#include <wzy/gui/view.hpp>

#include <wzy/core/engine.hpp>
#include <wzy/render/render.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {
namespace gui {

View::View(const UDim& position,
           const UDim& size) :
    Image(position, size),
    mFB(new render::FrameBuffer(size.currentAbs())) {

    setTexture(mFB->colourAttachment(0));
}


// ------------------------------------
void View::draw(const UDim& position,
                const Vector2f& scale) {
    mFB->bind();
    render::clear();
    Engine::singleton().rootNode()->draw(Engine::singleton().rootNode()->transformation());
    render::FrameBuffer::useDefault();

    Image::draw(position, scale);
}

}
}
