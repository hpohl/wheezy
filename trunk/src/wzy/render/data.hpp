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
    typedef Buffer<Vector4f, BasicBuffer::Type::Array> VertexBuffer;
    typedef Buffer<Vector2f, BasicBuffer::Type::Array> TexCoordBuffer;
    typedef Buffer<Vector4f, BasicBuffer::Type::Array> ColourBuffer;

    Data();
    ~Data();

    void bind() const;
    void set() const;
    void draw() const;

    void setVertices(const std::shared_ptr<VertexBuffer>& buffer)
    { mVertexBuffer = buffer; }

    void setTexCoords(const std::shared_ptr<TexCoordBuffer>& buffer)
    { mTexCoordBuffer = buffer; }

    void setColors(const std::shared_ptr<ColourBuffer>& buffer)
    { mColorBuffer = buffer; }

private:
    unsigned int mName;
    std::shared_ptr<VertexBuffer> mVertexBuffer;
    std::shared_ptr<TexCoordBuffer> mTexCoordBuffer;
    std::shared_ptr<ColourBuffer> mColorBuffer;
};

}
}

#endif
