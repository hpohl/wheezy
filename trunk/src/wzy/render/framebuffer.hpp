#ifndef WZY_RENDER_FRAMEBUFFER_HPP
#define WZY_RENDER_FRAMEBUFFER_HPP

#include <memory>
#include <vector>

#include <wzy/render/texture.hpp>
#include <wzy/utilities/noncopyable.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {
namespace render {

class FrameBuffer : public NonCopyable {
public:
    static void useDefault();
    static const Vector2i currentSize();

    FrameBuffer(const Vector2i& size);
    ~FrameBuffer();

    void bind() const;
    bool bound() const;

    bool valid() const;
    void validate() const;

    const std::shared_ptr<const Texture2D> colourAttachment(size_t i) const
    { return mColourAttachments.at(i); }

    const std::shared_ptr<Texture2D> colourAttachment(size_t i)
    { return mColourAttachments.at(i); }

private:
    std::shared_ptr<unsigned int> mName;
    std::vector<std::shared_ptr<Texture2D> > mColourAttachments;
    std::shared_ptr<unsigned int> mRenderBuffer;
    Vector2i mSize;
};

}
}

#endif
