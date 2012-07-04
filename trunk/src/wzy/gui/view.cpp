#include <wzy/gui/view.hpp>

#include <wzy/render/render.hpp>
#include <wzy/scene/camera.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {
namespace gui {

View::View(const std::shared_ptr<AbstractSceneNode>& node,
           const UDim& position,
           const UDim& size,
           const Vector2i& frameBufferSize) :
    Image(position, size),
    mSceneNode(validate(node)),
    mFB(new render::FrameBuffer(frameBufferSize == Vector2i(0, 0) ? size.currentAbs() : frameBufferSize)),
    mCamera(new Camera) {

    setTexture(mFB->colourAttachment(0));
}


// ------------------------------------
void View::draw(const UDim& position,
                const Vector2f& scale) {
    render::FrameBuffer::Pusher pusher(mFB);

    Matrix4f transf;
    auto rot = camera()->orientation();
    inverse(rot);
    rotate(transf, rot);
    translate(transf, -camera()->position());

    render::setViewport(Vector2i(0, 0), mFB->colourAttachment(0)->size());
    render::clear();
    mSceneNode->draw(camera()->projection(), transf);

    pusher.pop();

    render::setViewport(Vector2i(0, 0), render::FrameBuffer::currentSize());
    Image::draw(position, scale);
}

}
}
