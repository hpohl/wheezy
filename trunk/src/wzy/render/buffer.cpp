#include <wzy/render/buffer.hpp>

#include <wzy/render/glew.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

namespace {

GLenum typeToGL(BasicBuffer::Type t) {
    switch (t) {
    case BasicBuffer::Type::Array: return GL_ARRAY_BUFFER;
    case BasicBuffer::Type::Texture: return GL_TEXTURE_BUFFER;
    default: throw Exception("Uknown BasicBuffer type.");
    }
}

GLenum usageToGL(BasicBuffer::Usage u) {
    switch (u) {
    case BasicBuffer::Usage::StaticDraw: return GL_STATIC_DRAW;
    default: throw Exception("Unknown BasicBuffer usage.");
    }
}

}


// -------------------------------------------------
BasicBuffer::BasicBuffer(Type t, Usage u) :
    mName(0),
    mType(t),
    mUsage(u),
    mSize(0) {

    glGenBuffers(1, &mName);
    if (!mName)
        throw Exception("Unable to create BasicBuffer.");
}

BasicBuffer::~BasicBuffer() {
    glDeleteBuffers(1, &mName);
}


// --------------------------------------------
void BasicBuffer::bind() {
    glBindBuffer(typeToGL(mType), mName);

    if (!bound())
        throw Exception("Unable to bind BasicBuffer.");
}

void BasicBuffer::unbind() {
    glBindBuffer(typeToGL(mType), 0);
}

bool BasicBuffer::bound() const {
    GLenum target = 0;

    switch (mType) {
    case Type::Array:
        target = GL_ARRAY_BUFFER_BINDING;
        break;

    default:
        throw Exception ("Unknown BasicBuffer type.");
    }

    GLint name = 0;

    glGetIntegerv(target, &name);

    return name == mName;
}


// --------------------------------------------------
void BasicBuffer::setData(size_t size, const void* data) {
    bind();

    glGetError();
    glBufferData(typeToGL(mType), size, data, usageToGL(mUsage));

    if (glGetError() != GL_NO_ERROR)
        throw Exception("Unable to set BasicBuffer data.");

    mSize = size;
}

void BasicBuffer::updateData(size_t offset, size_t size, const void* data) {
    bind();

    glGetError();
    glBufferSubData(typeToGL(mType), offset, size, data);

    if (glGetError() != GL_NO_ERROR)
        throw Exception("Unable to update BasicBuffer data.");
}

}
}
