#include <wzy/render/texture.hpp>

#include <wzy/render/glew.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

namespace {

GLenum typeToGL(BasicTexture::Type t) {
    switch (t) {
    case BasicTexture::Type::OneD: return GL_TEXTURE_1D;
    case BasicTexture::Type::TwoD: return GL_TEXTURE_2D;
    case BasicTexture::Type::ThreeD: return GL_TEXTURE_3D;
    default: throw Exception("Unknown texture type.");
    }
}

GLenum typeToBinding(BasicTexture::Type t) {
    switch (t) {
    case BasicTexture::Type::OneD: return GL_TEXTURE_BINDING_1D;
    case BasicTexture::Type::TwoD: return GL_TEXTURE_BINDING_2D;
    case BasicTexture::Type::ThreeD: return GL_TEXTURE_BINDING_3D;
    default: throw Exception("Unknown texture type.");
    }
}

}


// ------------------------------------------
void BasicTexture::activateSlot(int s) {
    glActiveTexture(GL_TEXTURE0 + s);
    GLint slot = 0;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &slot);
    if (slot != GL_TEXTURE0 + s)
        throw Exception("Failed to set texture slot.");
}


// --------------------------------------
BasicTexture::BasicTexture(Type t) :
    mName(0),
    mType(t) {

    glGenTextures(1, &mName);
    if (!mName)
        throw Exception("Unable to create texture.");
}

BasicTexture::~BasicTexture() {
    glDeleteTextures(1, &mName);
}


// -------------------------------------------
void BasicTexture::bind() const {
    glBindTexture(typeToGL(mType), mName);
    if (!bound())
        throw Exception("Failed to bind texture.");
}

bool BasicTexture::bound() const {
    GLint name;
    glGetIntegerv(typeToBinding(mType), &name);
    return (name == static_cast<GLint>(mName));
}


// ------------------------------------------------
void BasicTexture::setData(const Vector2i& size, int bpp, const unsigned char* data) {
    assert(mType == Type::TwoD);

    bind();

    GLenum internalFormat = 0;

    switch (bpp) {
    case 8: internalFormat = GL_RED; break;
    case 24: internalFormat = GL_RGB; break;
    case 32: internalFormat = GL_RGBA; break;
    default: throw Exception("Unknown bpp in BasicTexture::setData.");
    }

    glTexImage2D(typeToGL(mType), 0, internalFormat, size.x(), size.y(),
                 0, internalFormat, GL_UNSIGNED_BYTE, data);
}

}
}
