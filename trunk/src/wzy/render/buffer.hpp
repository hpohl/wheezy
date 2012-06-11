#ifndef WZY_RENDER_BUFFER_HPP
#define WZY_RENDER_BUFFER_HPP

#include <utility>
#include <vector>

#include <cstddef>

#include <wzy/render/program.hpp>
#include <wzy/utilities/noncopyable.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {
namespace render {

class AbstractBasicBuffer : public NonCopyable {
public:
    enum class Type {
        Array,
        ElementArray,
        Uniform
    };

    enum class Usage {
        StreamDraw, StreamRead, StreamCopy,
        StaticDraw, StaticRead, StaticCopy,
        DynamicDraw, DynamicRead, DynamicCopy
    };


    AbstractBasicBuffer(Type t, Usage u);
    virtual ~AbstractBasicBuffer() = 0;

    unsigned int name() const
    { return mName; }

    Type type() const
    { return mType; }

    Usage usage() const
    { return mUsage; }

    void bind() const;
    void bindBase(unsigned int index);
    void unbind() const;
    bool bound() const;

    void setData(size_t size, const void* data);
    void updateData(size_t offset, size_t size, const void* data);

    size_t size() const
    { return mSize; }

private:
    unsigned int mName;
    const Type mType;
    const Usage mUsage;
    size_t mSize;
};


// ------------------------------------------------
template <AbstractBasicBuffer::Type ttype, AbstractBasicBuffer::Usage tusage>
class AbstractBuffer : public AbstractBasicBuffer {
public:
    template <class... Args>
    AbstractBuffer(Args&&... args) :
        AbstractBasicBuffer(ttype, tusage, std::forward<Args>(args)...) { }

    virtual ~AbstractBuffer() = 0;
};

template <AbstractBasicBuffer::Type ttype, AbstractBasicBuffer::Usage usage>
AbstractBuffer<ttype, usage>::~AbstractBuffer() { }

template <AbstractBasicBuffer::Type ttype, AbstractBasicBuffer::Usage usage>
class Buffer final : public AbstractBuffer<ttype, usage> {
public:
    template <class... Args>
    Buffer(Args&&... args) :
        AbstractBuffer<ttype, usage>(std::forward<Args>(args)...) { }
};


// ---------------------------------------------------
template <class T, AbstractBasicBuffer::Usage usage>
class ArrayBuffer : public AbstractBuffer<AbstractBasicBuffer::Type::Array, usage> {
public:
    typedef AbstractBuffer<AbstractBasicBuffer::Type::Array, usage> Parent;


    template <class... Args>
    ArrayBuffer(Args&&... args) :
        AbstractBuffer<AbstractBasicBuffer::Type::Array, usage>(std::forward<Args>(args)...) { }

    void setData(const std::vector<T>& data)
    { Parent::setData(data.size() * sizeof(T), data.data()); }

    void setData(size_t offset, std::vector<T>& data)
    { Parent::setData(offset * sizeof(T), data.size() * sizeof(T), data.data()); }

    size_t count() const
    { return Parent::size() / sizeof(T); }
};


// -----------------------------------------------
class UniformBuffer : public AbstractBuffer<AbstractBasicBuffer::Type::Uniform,
        AbstractBasicBuffer::Usage::DynamicDraw> {
public:
    template <typename T>
    struct Item {
        const std::string name;
        const T val;
    };

    typedef Item<double> DoubleItem;
    typedef Item<int> IntItem;
    typedef Item<float> FloatItem;

    typedef Item<Vector2f> Vec2Item;
    typedef Item<Vector3f> Vec3Item;
    typedef Item<Vector4f> Vec4Item;


    template <class... Args>
    UniformBuffer(const std::shared_ptr<Program>& prog, Args&&... args) :
        AbstractBuffer<AbstractBasicBuffer::Type::Uniform,
        AbstractBasicBuffer::Usage::DynamicDraw>(std::forward<Args>(args)...),
        mProg(prog) {
    }

private:
    const std::shared_ptr<Program> mProg;
};


}
}

#endif
