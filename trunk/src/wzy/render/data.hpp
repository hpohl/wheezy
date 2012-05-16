#ifndef WZY_RENDER_DATA_HPP
#define WZY_RENDER_DATA_HPP

#include <memory>

#include <wzy/render/buffer.hpp>
#include <wzy/utilities/noncopyable.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {
namespace render {

class Data final : public NonCopyable {
public:
    typedef ArrayBuffer<Vector4f, AbstractBasicBuffer::Usage::StaticDraw> VertexBuffer;
    typedef ArrayBuffer<Vector2f, AbstractBasicBuffer::Usage::StaticDraw> TexCoordBuffer;
    typedef ArrayBuffer<Vector4f, AbstractBasicBuffer::Usage::StaticDraw> ColourBuffer;

    Data();
    Data(const std::shared_ptr<const VertexBuffer>& vertices,
         const std::shared_ptr<const ColourBuffer>& colours = std::shared_ptr<const ColourBuffer>(),
         const std::shared_ptr<const TexCoordBuffer>& texCoords = std::shared_ptr<const TexCoordBuffer>());
    ~Data();

    void bind() const;
    void set() const;
    void draw() const;

    void setVertices(const std::shared_ptr<const VertexBuffer>& buffer)
    { mVertexBuffer = buffer; }

    void setTexCoords(const std::shared_ptr<const TexCoordBuffer>& buffer)
    { mTexCoordBuffer = buffer; }

    void setColours(const std::shared_ptr<const ColourBuffer>& buffer)
    { mColourBuffer = buffer; }

private:
    unsigned int mName;
    std::shared_ptr<const VertexBuffer> mVertexBuffer;
    std::shared_ptr<const ColourBuffer> mColourBuffer;
    std::shared_ptr<const TexCoordBuffer> mTexCoordBuffer;
};

}
}

#endif
