#include <wzy/render/buffer.hpp>

#include <map>

#include <wzy/render/glew.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

namespace {

struct TypeInfo {
    GLenum target;
    GLenum binding;
};

std::map<AbstractBasicBuffer::Type, TypeInfo> typeMap = {
    {AbstractBasicBuffer::Type::Array, {GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING}},
    {AbstractBasicBuffer::Type::Uniform, {GL_UNIFORM_BUFFER, GL_UNIFORM_BUFFER_BINDING}}
};

const TypeInfo typeToInfo(AbstractBasicBuffer::Type t) {
    auto it = typeMap.find(t);
    if (it == typeMap.end())
        throw Exception("Unkwnone buffer type.");
    return it->second;
}

GLenum typeToTarget(AbstractBasicBuffer::Type t)
{ return typeToInfo(t).target; }

GLenum typeToBinding(AbstractBasicBuffer::Type t)
{ return typeToInfo(t).binding; }


// --------------------------------------------------
std::map<AbstractBasicBuffer::Usage, GLenum> usageMap = {
    {AbstractBasicBuffer::Usage::StaticDraw, GL_STATIC_DRAW}
};

GLenum usageToGL(AbstractBasicBuffer::Usage u) {
    auto it = usageMap.find(u);
    if (it == usageMap.end())
        throw Exception("Unknown buffer usage.");
    return it->second;
}

}


// -------------------------------------------------
AbstractBasicBuffer::AbstractBasicBuffer(Type t, Usage u) :
    mName(0),
    mType(t),
    mUsage(u),
    mSize(0) {

    glGenBuffers(1, &mName);
    if (!mName)
        throw Exception("Unable to create AbstractBasicBuffer.");
}

AbstractBasicBuffer::~AbstractBasicBuffer() {
    glDeleteBuffers(1, &mName);
}


// --------------------------------------------
void AbstractBasicBuffer::bind() const {
    glBindBuffer(typeToTarget(mType), mName);

    if (!bound())
        throw Exception("Unable to bind AbstractBasicBuffer.");
}

void AbstractBasicBuffer::bindBase(unsigned int index) {
    glBindBufferBase(typeToTarget(mType), index, mName);
}

void AbstractBasicBuffer::unbind() const {
    glBindBuffer(typeToTarget(mType), 0);
}

bool AbstractBasicBuffer::bound() const {
    GLint name = 0;
    glGetIntegerv(typeToBinding(mType), &name);
    return (name == static_cast<GLint>(mName));
}


// --------------------------------------------------
void AbstractBasicBuffer::setData(size_t size, const void* data) {
    bind();
    glBufferData(typeToTarget(mType), size, data, usageToGL(mUsage));
    mSize = size;
}

void AbstractBasicBuffer::updateData(size_t offset, size_t size, const void* data) {
    bind();
    glBufferSubData(typeToTarget(mType), offset, size, data);
}

}
}
