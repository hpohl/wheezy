#ifndef WZY_RENDER_BUFFER_HPP
#define WZY_RENDER_BUFFER_HPP

#include <utility>
#include <vector>

#include <cstddef>

#include <wzy/utilities/noncopyable.hpp>


namespace wzy {
namespace render {

class BasicBuffer : public NonCopyable {
public:
    enum class Type {
        Array,
        ElementArray,
        PixelPack,
        PixelUnpack,
        Texture
    };

    enum class Usage {
        StreamDraw, StreamRead, StreamCopy,
        StaticDraw, StaticRead, StaticCopy,
        DynamicDraw, DynamicRead, DynamicCopy
    };

    template <class T, Type ttype, Usage usage>
    friend class Buffer;


    BasicBuffer(Type t, Usage u);
    virtual ~BasicBuffer() = 0;

    unsigned int name() const
    { return mName; }

    Type type() const
    { return mType; }

    void bind();
    void unbind();

    bool bound() const;

private:
    unsigned int mName;
    const Type mType;
    const Usage mUsage;
    size_t mSize;

    size_t size() const
    { return mSize; }

    void setData(size_t size, const void* data);
    void updateData(size_t offset, size_t size, const void* data);
};


template <class T, BasicBuffer::Type ttype, BasicBuffer::Usage usage = BasicBuffer::Usage::StaticDraw>
class Buffer final : public BasicBuffer {
public:
    template <class... Args>
    Buffer(Args&&... args) :
        BasicBuffer(ttype, usage, std::forward<Args>(args)...) {
    }

    void setData(const std::vector<T>& data)
    { BasicBuffer::setData(data.size() * sizeof(T), data.data()); }

    size_t size() const
    { return BasicBuffer::size() / sizeof(T); }
};

}
}

#endif
