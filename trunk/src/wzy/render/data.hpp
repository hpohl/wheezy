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
    typedef Buffer<Vector4f, BasicBuffer::Type::Array, BasicBuffer::Usage::StaticDraw> VertexBuffer;

    Data();
    ~Data();

    void bind() const;
    void set() const;
    void draw() const;

    void setVertices(const std::shared_ptr<VertexBuffer>& buffer)
    { mVertexBuffer = buffer; }

private:
    unsigned int mName;
    std::shared_ptr<VertexBuffer> mVertexBuffer;
};

}
}

#endif
